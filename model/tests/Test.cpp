//
// Created by - on 20.12.2022.
//

#include "Test.h"
#include <cassert>

void testTopologicalSort() {
    Graph<int> graph = Graph<int>();
    Vertex vertex0 = { "0" };
    Vertex vertex1 = { "1" };
    Vertex vertex2 = { "2" };
    Vertex vertex3 = { "3" };
    graph.addVertex(vertex0);
    graph.addVertex(vertex1);
    graph.addVertex(vertex2);
    graph.addVertex(vertex3);
    Edge<int> edge0 = Edge(vertex0, vertex3, 1);
    Edge<int> edge1 = Edge(vertex3, vertex1, 2);
    Edge<int> edge2 = Edge(vertex3, vertex2, 3);
    Edge<int> edge3 = Edge(vertex2, vertex1, 4);
    graph.addEdge(edge0);
    graph.addEdge(edge1);
    graph.addEdge(edge2);
    graph.addEdge(edge3);
    vector<Vertex> sorted = graph.topologicalSortResult();
    vector<Vertex> needed = vector<Vertex>();
    needed.push_back(vertex0);
    needed.push_back(vertex1);
    needed.push_back(vertex2);
    needed.push_back(vertex3);
    for (int i = 0; i < needed.size(); ++i) {
        assert(needed[i] == sorted[i]);
    }
}

void testConnectivityComponents() {
    Graph<int> graph = Graph<int>();
    Vertex vertex0 = { "0" };
    Vertex vertex1 = { "1" };
    Vertex vertex2 = { "2" };
    Vertex vertex3 = { "3" };
    graph.addVertex(vertex0);
    graph.addVertex(vertex1);
    graph.addVertex(vertex2);
    graph.addVertex(vertex3);
    Edge<int> edge0 = Edge(vertex0, vertex3, 1);
    Edge<int> edge1 = Edge(vertex3, vertex1, 2);
    Edge<int> edge2 = Edge(vertex3, vertex2, 3);
    Edge<int> edge3 = Edge(vertex2, vertex1, 4);
    graph.addEdge(edge0);
    graph.addEdge(edge1);
    graph.addEdge(edge2);
    graph.addEdge(edge3);
    vector<Vertex> needed = vector<Vertex>();
    needed.push_back(vertex0);
    needed.push_back(vertex1);
    needed.push_back(vertex2);
    needed.push_back(vertex3);
    vector<vector<Vertex>> connectivityComponents = graph.connectivityComponentsResult();
    vector<vector<Vertex>> required = vector<vector<Vertex>>();
    required.push_back(needed);
    sort(required.begin(), required.end());
    sort(connectivityComponents.begin(), connectivityComponents.end());
    for (int i = 0; i < required.size(); ++i) {
        sort(required[i].begin(), required[i].end());
        sort(connectivityComponents[i].begin(), connectivityComponents[i].end());
        for (int j  = 0; j < required[i].size(); ++j) {
            assert(required[i][j] == connectivityComponents[i][j]);
        }
    }
}

void testShortestPaths() {
    Graph<int> graph = Graph<int>();
    Vertex vertex0 = { "0" };
    Vertex vertex1 = { "1" };
    Vertex vertex2 = { "2" };
    Vertex vertex3 = { "3" };
    graph.addVertex(vertex0);
    graph.addVertex(vertex1);
    graph.addVertex(vertex2);
    graph.addVertex(vertex3);
    Edge<int> edge0 = Edge(vertex0, vertex3, 1);
    Edge<int> edge1 = Edge(vertex3, vertex1, 2);
    Edge<int> edge2 = Edge(vertex3, vertex2, 3);
    Edge<int> edge3 = Edge(vertex2, vertex1, 4);
    graph.addEdge(edge0);
    graph.addEdge(edge1);
    graph.addEdge(edge2);
    graph.addEdge(edge3);
    pair<Vertex, Vertex> pair1 = make_pair(vertex0, vertex1);
    pair<Vertex, Vertex> pair2 = make_pair(vertex0, vertex2);
    pair<Vertex, Vertex> pair3 = make_pair(vertex0, vertex3);
    pair<Vertex, Vertex> pair4 = make_pair(vertex1, vertex2);
    pair<Vertex, Vertex> pair5 = make_pair(vertex1, vertex3);
    pair<Vertex, Vertex> pair6 = make_pair(vertex2, vertex3);
    map<pair<Vertex, Vertex>, int> paths = graph.findTheShortestPaths();
    map<pair<Vertex, Vertex>, int> needed = map<pair<Vertex, Vertex>, int>();
    needed[pair1] = 3;
    needed[pair2] = 4;
    needed[pair3] = 1;
    needed[pair4] = 4;
    needed[pair5] = 2;
    needed[pair6] = 3;
    assert(needed[pair1] == paths[pair1]);
    assert(needed[pair2] == paths[pair2]);
    assert(needed[pair3] == paths[pair3]);
    assert(needed[pair4] == paths[pair4]);
    assert(needed[pair5] == paths[pair5]);
    assert(needed[pair6] == paths[pair6]);
}

void testFindMinimalSkeleton() {

}

void runTests() {
    testConnectivityComponents();
    testFindMinimalSkeleton();
    testShortestPaths();
    //testTopologicalSort();
}
