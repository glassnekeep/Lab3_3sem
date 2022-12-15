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
    void dfs(Vertex& start, map<Vertex, bool>& used, vector<Vertex>& topSort, vector<pair<Vertex, vector<Edge<T>>>> array, bool isCircle);
    void Deikstra()
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
void Graph<T>::dfs(Vertex& vertex, map<Vertex, bool> &used, vector<Vertex> &topSort, vector<pair<Vertex, vector<Edge<T>>>> array, bool isCircle) {
    used[vertex] = true;
    int index = getVertexIndex(vertex);
    for (int i = 0; i < list.size(); ++i) {

    }
    //TODO Finish later, need to fix issue with
}


#endif //LAB3_3SEM_GRAPH_H
