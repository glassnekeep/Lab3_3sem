//
// Created by glass on 13.12.2022.
//

#ifndef LAB3_3SEM_GRAPH_H
#define LAB3_3SEM_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct Vertex {
    string name;
};

template <typename T>
class Edge {
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
};

template <typename T>
class Graph {
    vector<pair<Vertex, vector<Edge<T>>>> list; //Incidence list
public:
    Graph();
    Graph(vector<pair<Vertex, vector<Edge<T>>>> newList) {
        list = newList;
    };
    bool findVertex(Vertex& vertex);
    int getVertexIndex(Vertex& vertex);
    void addEdge(Vertex& startVertex, Vertex& endVertex, T& val);
    void addVertex(Vertex& vertex);
    void removeVertex(Vertex& vertex);
    void removeEdge(Edge<T>& edge);
    Vertex getNext(Vertex& vertex);
    void dfsForTopologicalSort(Vertex& vertex, map<Vertex, int>& used, vector<Vertex>& topSort, vector<pair<Vertex, vector<Edge<T>>>> array, bool& isCircle);
    void topologicalSort(map<Vertex, int>& used, vector<Vertex>& topSort, vector<pair<Vertex, vector<Edge<T>>>> array, int n, bool& isCircle);
    vector<Vertex> topologicalSortResult();
    void dfsForConnectivityComponents(Vertex& vertex, map<Vertex, int>& used, vector<pair<Vertex, vector<Edge<T>>>>& array, vector<Vertex>& components);
    void countComponents(map<Vertex, int>& used, vector<pair<Vertex, vector<Edge<T>>>>& array, vector<Vertex>& components, vector<vector<Vertex>>& allComponents);
    vector<vector<Vertex>> connectivityComponentsResult();
    //Here should be strong connectivity components;
    map<pair<Vertex, Vertex>, T> findTheShortestPaths(); //Floyd algorithm
    void Deikstra();
    ~Graph();
};

template<typename T>
bool Graph<T>::findVertex(Vertex &vertex) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first == vertex) return true;
    }
    return false;
}

template<typename T>
int Graph<T>::getVertexIndex(Vertex &vertex) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first == vertex) return i;
    }
    return -1;
}

template<typename T>
void Graph<T>::addEdge(Vertex &startVertex, Vertex &endVertex, T &val) {
    Edge<T>* newEdge = new Edge(startVertex, endVertex, val);
    int firstIndex = getVertexIndex(startVertex);
    int secondIndex = getVertexIndex(endVertex);
    if (firstIndex != - 1 && secondIndex != -1) {
        list[firstIndex].second.push_back(newEdge);
        list[secondIndex].second.push_back(newEdge);
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
        Vertex next = list[index].second[i].vertex2;
        if (used[next] == 1) {
            isCircle = true;
            return;
        } else if (used[next] == 0) dfs(next, used, topSort, array, isCircle);
        if (isCircle) return;
    }
    used[vertex] = 2;
    topSort.push_back(vertex);
    //Looks like it should work
}

template<typename T>
void Graph<T>::topologicalSort(map<Vertex, int> &used, vector<Vertex> &topSort, vector<pair<Vertex, vector<Edge<T>>>> array, int n, bool& isCircle) {
    for (int i = 0; i < n; ++i ) {
        Vertex vertex = getVertexIndex(i);
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
        Vertex next = list[index].second[i].vertex2;
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
            Vertex vertex1 = list[i].second[j].vertex1;
            Vertex vertex2 = list[i].second[j].vertex2;
            T value = list[i].second[j].value;
            pair<Vertex, Vertex> pair = make_pair(vertex1, vertex2);
            matrix[pair] = value;
        }
    }
    for (int k = 0; k < list.size(); ++k) {
        for (int i = 0; i < list.size(); ++i) {
            for (int j = 0; j < list.size(); ++j) {
                pair<Vertex, Vertex> pair1 = make_pair(list[i], list[j]);
                pair<Vertex, Vertex> pair2 = make_pair(list[i], list[k]);
                pair<Vertex, Vertex> pair3 = make_pair(list[k], list[j]);
                matrix[pair1] = min(matrix[pair1], matrix[pair2] + matrix[pair3]);
            }
        }
    }
    return matrix;
}


#endif //LAB3_3SEM_GRAPH_H
