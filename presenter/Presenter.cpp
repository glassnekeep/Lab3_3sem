//
// Created by - on 18.12.2022.
//

#include "Presenter.h"

using namespace std;

template<typename T>
void Presenter<T>::generateGraph(int count) {
    size = count;
    vector<pair<Vertex, vector<Edge<T>>>> array = vector<pair<Vertex, vector<Edge<T>>>>();
    vector<vector<int>> matrix = vector<vector<int>>();
    matrix.assign(count, vector<int>(count));
    for (int i = 0; i < count; ++i) {
        Vertex vertex = {to_string(i)};
        array.push_back(make_pair(vertex, vector<Edge<T>>()));
    }
    graph = Graph<int>(array);
    int edgeCount = rand() % ((count * (count - 1)) / 2);
    for (int i = 0; i < edgeCount; ++i) {
        Vertex vertex1 = { to_string(rand() % count) };
        Vertex vertex2 = { to_string(rand() % count) };
        int value = rand() % 40;
        Edge<int> edge = Edge<int>(vertex1, vertex2, value);
        graph.addEdge(edge);
    }
}

template<typename T>
string Presenter<T>::topologicalSort() {
    if (graph.connectivityComponentsResult().size() > 1) return "The graph contains more than 1 component of connectivity";
    vector<Vertex> array = graph.topologicalSortResult();
    string result = "Topological sort array:\n";
    for (int i = 0; i < result.size(); ++i) {
        result += "Vertex: " + array[i].name + "\n";
    }
    return result;
}

template<typename T>
string Presenter<T>::connectivityComponents() {
    vector<vector<Vertex>> array = graph.connectivityComponentsResult();
    string result = "Connectivity components:\n";
    for (int i = 0; i < array.size(); ++i) {
        result += string("Connectivity component №") + to_string(i) + ":";
        for (auto & j : array[i]) {
            result += " " + j.name + ",";
        }
        result += "\n";
    }
    return result;
}

template<typename T>
string Presenter<T>::findShortestPaths() {
    map<pair<Vertex, Vertex>, int> paths = graph.findTheShortestPaths();
    string result = "Shortest paths:\n";
    for (auto& item: paths) {
        result += "Vertex1 = " + item.first.first.name + ", vertex2 = " + item.first.second.name, ", path = " + to_string(item.second) + "\n";
    }
    return result;
}

template<typename T>
string Presenter<T>::findTheMinimumSkeleton() {
    if (graph.connectivityComponentsResult().size() > 1) return "Impossible to find skeleton cause the graph contains more than 1 component of connectivity";
    vector<Edge<int>> skeleton = graph.findTheMinimumSkeleton();
    string result = "Minimum skeleton:\n";
    for (auto& item: skeleton) {
        result += item.toString() + "\n";
    }
    return result;
}

template<typename T>
string Presenter<T>::printGraph() {
    return graph.printGraph();
}