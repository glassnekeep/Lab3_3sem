//
// Created by - on 18.12.2022.
//

#include "Presenter.h"

using namespace std;

void Presenter::generateGraph(int count) {
    size = count;
    vector<pair<Vertex, vector<Edge<int>>>> array = vector<pair<Vertex, vector<Edge<int>>>>();
    vector<vector<int>> matrix = vector<vector<int>>();
    matrix.assign(count, vector<int>(count));
    for (int i = 0; i < count; ++i) {
        Vertex vertex = {to_string(i)};
        array.emplace_back(vertex, vector<Edge<int>>());//Changed push_back because of IDE hint, may require fixes
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

string Presenter::topologicalSort() {
    if (graph.connectivityComponentsResult().size() > 1) return "The graph contains more than 1 component of connectivity\n";
    vector<Vertex> array = graph.topologicalSortResult();
    string result = "Topological sort array:\n";
    for (int i = 0; i < result.size(); ++i) {
        result += "Vertex: " + array[i].name + "\n";
    }
    return result;
}

string Presenter::connectivityComponents() {
    vector<vector<Vertex>> array = graph.connectivityComponentsResult();
    string result = "Connectivity components:\n";
    for (int i = 0; i < array.size(); ++i) {
        result += string("Connectivity component #") + to_string(i) + ":";
        for (auto & j : array[i]) {
            result += " " + j.name + ",";
        }
        result += "\n";
    }
    return result;
}

string Presenter::findShortestPaths() {
    map<pair<Vertex, Vertex>, int> paths = graph.findTheShortestPaths();
    string result = "Shortest paths:\n";
    for (auto& item: paths) {
        result += "Vertex1 = " + item.first.first.name + ", vertex2 = " + item.first.second.name, ", path = " + to_string(item.second) + "\n";
    }
    return result;
}

string Presenter::findTheMinimumSkeleton() {
    if (graph.connectivityComponentsResult().size() > 1) return "Impossible to find skeleton cause the graph contains more than 1 component of connectivity\n";
    vector<Edge<int>> skeleton = graph.findTheMinimumSkeleton();
    string result = "Minimum skeleton:\n";
    for (auto& item: skeleton) {
        result += item.toString() + "\n";
    }
    return result;
}

string Presenter::printGraph() {
    return graph.printGraph();
}