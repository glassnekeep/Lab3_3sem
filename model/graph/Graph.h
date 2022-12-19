//
// Created by glass on 13.12.2022.
//

#ifndef LAB3_3SEM_GRAPH_H
#define LAB3_3SEM_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Vertex {
    string name;

    bool operator==(const Vertex& vertex) const {
        return vertex.name == this -> name;
    }

    bool operator<(const Vertex& vertex) const {
        return this -> name < vertex.name;
    }
};

template <typename T>
class Edge {
private:
    Vertex vertex1;
    Vertex vertex2;
    T value;
public:
    Edge(const Vertex& startVertex, const Vertex& endVertex, const T& val) {
        vertex1 = startVertex;
        vertex2 = endVertex;
        value = val;
    }
    ~Edge();

    Vertex getFirstVertex() {
        return vertex1;
    }

    Vertex getSecondVertex() {
        return vertex2;
    }

    T getValue() {
        return value;
    }

    bool operator==(const Edge<T>& edge) const {
        return edge.vertex1 == this -> vertex1 && edge.vertex2 == this -> vertex2 && edge.value == this -> value;
    }

    bool operator<(const Edge<T>& edge) const {
        return this -> value < edge.value;
    }

    string toString() {
        return "Edge: vertex1 = " + vertex1.name + ", vertex2 = " + vertex2.name + ", value = " + to_string(value);
    }
};

template <typename T>
bool compareByValue(const Edge<T>& edge1, const Edge<T>& edge2) {
    return (edge1.getValue() < edge2.getValue());
}

template <typename T>
class Graph {
    vector<pair<Vertex, vector<Edge<T>>>> list; //Incidence list
private:
    int getVertexIndex(Vertex vertex);
    Vertex getNext(Vertex& vertex);
    void dfsForTopologicalSort(Vertex& vertex, map<Vertex, int>& used, vector<Vertex>& topSort, vector<pair<Vertex, vector<Edge<T>>>> array, bool& isCircle);
    void topologicalSort(map<Vertex, int>& used, vector<Vertex>& topSort, vector<pair<Vertex, vector<Edge<T>>>> array, int n, bool& isCircle);
    void dfsForConnectivityComponents(Vertex& vertex, map<Vertex, int>& used, vector<pair<Vertex, vector<Edge<T>>>>& array, vector<Vertex>& components);
    void countComponents(map<Vertex, int>& used, vector<pair<Vertex, vector<Edge<T>>>>& array, vector<Vertex>& components, vector<vector<Vertex>>& allComponents);
    int countEdges();
public:
    Graph() = default;
    explicit Graph(vector<pair<Vertex, vector<Edge<T>>>> newList) {
        list = newList;
    };
    bool findVertex(Vertex& vertex);
    void addEdge(Edge<T>& edge);
    void addVertex(Vertex& vertex);
    void removeVertex(Vertex& vertex);
    void removeEdge(Edge<T>& edge);
    vector<Vertex> topologicalSortResult();
    vector<vector<Vertex>> connectivityComponentsResult();
    //Here should be strong connectivity components;
    map<pair<Vertex, Vertex>, T> findTheShortestPaths(); //Floyd's algorithm
    vector<Edge<T>> findTheMinimumSkeleton(); //Kruskal's algorithm
    string printGraph();
    ~Graph() = default;
};

template<typename T>
bool Graph<T>::findVertex(Vertex &vertex) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first == vertex) return true;
    }
    return false;
}

template<typename T>
int Graph<T>::getVertexIndex(Vertex vertex) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first == vertex) return i;
    }
    return -1;
}

template<typename T>
void Graph<T>::addEdge(Edge<T>& edge) {
    int firstIndex = getVertexIndex(edge.getFirstVertex());
    int secondIndex = getVertexIndex(edge.getSecondVertex());
    if (firstIndex != -1 && secondIndex != -1) {
        list[firstIndex].second.push_back(edge);
        list[secondIndex].second.push_back(edge);
    }
    //TODO Here required to process the case where one of the vertexes does not belong to this graph
}

template<typename T>
void Graph<T>::addVertex(Vertex& vertex) {
    list.push_back(make_pair(vertex, vector<Edge<T>>(0)));
    //TODO Here required to process the case when Vertex with such name already exists
}

template<typename T>
void Graph<T>::removeVertex(Vertex &vertex) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first == vertex) {
            list.erase(vertex);
        }
    }
    //TODO Here required to process the case when this Vertex does not exist in the graph
}

template<typename T>
void Graph<T>::removeEdge(Edge<T> &edge) {
    Vertex firstVertex = edge.vertex1;
    Vertex secondVertex = edge.vertex2;
    int firstIndex = getVertexIndex(firstVertex);
    int secondIndex = getVertexIndex(secondIndex);
    if (firstIndex != -1 && secondIndex != -1) {
        list[firstIndex].second.erase(edge);
        list[secondIndex].second.erase(edge);
    }
    //TODO Here required to process the case when this Edge does not belong to the Graph
}

template<typename T>
Vertex Graph<T>::getNext(Vertex& vertex) {
    int index = getVertexIndex(vertex);
    return list[index].second[0].vertex2;
}

template<typename T>
void Graph<T>::dfsForTopologicalSort(Vertex& vertex, map<Vertex, int> &used, vector<Vertex> &topSort, vector<pair<Vertex, vector<Edge<T>>>> array, bool& isCircle) {
    used[vertex] = 1;
    int index = getVertexIndex(vertex);
    for (int i = 0; i < list[index].second.size(); ++i) {
        Vertex next = list[index].second[i].getSecondVertex();
        if (used[next] == 1) {
            isCircle = true;
            return;
        } else if (used[next] == 0) dfsForTopologicalSort(next, used, topSort, array, isCircle);
        if (isCircle) return;
    }
    used[vertex] = 2;
    topSort.push_back(vertex);
    //Looks like it should work
}

template<typename T>
void Graph<T>::topologicalSort(map<Vertex, int> &used, vector<Vertex> &topSort, vector<pair<Vertex, vector<Edge<T>>>> array, int n, bool& isCircle) {
    for (int i = 0; i < n; ++i ) {
        Vertex vertex = list[i].first;
        if (!used[vertex]) dfsForTopologicalSort(array[i].first, used, topSort, array, isCircle);
    }
    reverse(topSort.begin(), topSort.end());
}

template<typename T>
vector<Vertex> Graph<T>::topologicalSortResult() {
    map<Vertex, int> used = map<Vertex, int>();
    vector<Vertex> topSort = vector<Vertex>();
    bool isCircle = false;
    topologicalSort(used, topSort, list, list.size(), isCircle);
    if (isCircle) {
        throw invalid_argument("Graph contains a circle");
    } else {
        return topSort;
    }
}

template<typename T>
void Graph<T>::dfsForConnectivityComponents(Vertex &vertex, map<Vertex, int> &used,vector<pair<Vertex, vector<Edge<T>>>> &array, vector<Vertex> &components) {
    used[vertex] = 1;
    components.push_back(vertex);
    int index = getVertexIndex(vertex);
    for (int i = 0; i < list[index].second.size(); ++i) {
        Vertex next = list[index].second[i].getSecondVertex();
        if (!used[next]) dfsForConnectivityComponents(next, used, array, components);
    }
}

template<typename T>
void Graph<T>::countComponents(map<Vertex, int> &used, vector<pair<Vertex, vector<Edge<T>>>> &array,vector<Vertex> &components, vector<vector<Vertex>> &allComponents) {
    for (int i = 0; i < list.size(); ++i) {
        Vertex vertex = list[i].first;
        if (!used[vertex]) {
            components.clear();
            dfsForConnectivityComponents(vertex, used, array, components);
            allComponents.push_back(components);
        }
    }
}

template<typename T>
vector<vector<Vertex>> Graph<T>::connectivityComponentsResult() {
    map<Vertex, int> used = map<Vertex, int>();
    vector<Vertex> components = vector<Vertex>();
    vector<vector<Vertex>> allComponents = vector<vector<Vertex>>();
    countComponents(used, list, components, allComponents);
    return allComponents;
}

template<typename T>
map<pair<Vertex, Vertex>, T> Graph<T>::findTheShortestPaths() {
    map<pair<Vertex, Vertex>, T> matrix = map<pair<Vertex, Vertex>, T>();
    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < list[i].second.size(); ++j) {
            Vertex vertex1 = list[i].second[j].getFirstVertex();
            Vertex vertex2 = list[i].second[j].getSecondVertex();
            T value = list[i].second[j].getValue();
            pair<Vertex, Vertex> pair = make_pair(vertex1, vertex2);
            matrix[pair] = value;
        }
    }
    for (int k = 0; k < list.size(); ++k) {
        for (int i = 0; i < list.size(); ++i) {
            for (int j = 0; j < list.size(); ++j) {
                pair<Vertex, Vertex> pair1 = make_pair(list[i].first, list[j].first);
                pair<Vertex, Vertex> pair2 = make_pair(list[i].first, list[k].first);
                pair<Vertex, Vertex> pair3 = make_pair(list[k].first, list[j].first);
                matrix[pair1] = min(matrix[pair1], matrix[pair2] + matrix[pair3]);
            }
        }
    }
    return matrix;
}

template<typename T>
vector<Edge<T>> Graph<T>::findTheMinimumSkeleton() {
    set<Edge<T>> edgeSet = set<Edge<T>>();
    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < list[i].second.size(); ++j) {
            Edge<T> edge = list[i].second[j];
            edgeSet.insert(edge);
        }
    }
    vector<Edge<T>> edges = vector(edgeSet.begin(), edgeSet.end());
    vector<Edge<T>> result = vector<Edge<T>>();
    std::sort(edges.begin(), edges.end(), compareByValue);
    map<Vertex, int> tree = map<Vertex, int>();
    for (int i = 0; i < list.size(); ++i) {
        //Added this if myself because there might be a graph with more than 1 connectivity component
        if (!list[i].second.empty()) tree[list[i].first] = i;
    }
    int cost = 1;
    for (int i = 0; i < edges.size(); ++i) {
        Vertex vertex1 = edges[i].getFirstVertex();
        Vertex vertex2 = edges[i].getSecondVertex();
        T value = edges[i].getValue();
        if (tree[vertex1] != tree[vertex2]) {
            cost += 1;
            result.push_back(edges[i]);
            int oldId = tree[vertex2];
            int newId = tree[vertex1];
            for (int j = 0; j < list.size(); ++j) {
                Vertex vertex = list[i].first;
                if (tree[vertex] == oldId) {
                    tree[vertex] = newId;
                }
            }
        }
    }
    return result;
}

template<typename T>
int Graph<T>::countEdges() {
    int result = 0;
    for (int i = 0; i < list.size(); ++i) {
        result += list[i].second.size();
    }
    return result / 2;
}

template<typename T>
string Graph<T>::printGraph() {
    string result{};
    string graphInfo = string("Graph: vertexes = ") + to_string(list.size()) + ", edges = " + to_string(countEdges()) + "\n";
    string array = {};
    for (int i = 0; i < list.size(); ++i) {
        string currentVertex = string("Vertex: " + list[i].first.name + ", Edges: ");
        for (int j = 0; j < list[i].second.size(); ++j) {
            currentVertex += "(" + list[i].second[j].getFirstVertex().name + ", " + list[i].second[j].getSecondVertex().name + "), ";
        }
        array += currentVertex + "\n";
    }
    result += graphInfo + array;
    return result;
}


#endif //LAB3_3SEM_GRAPH_H
