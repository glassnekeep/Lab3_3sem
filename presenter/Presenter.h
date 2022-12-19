//
// Created by - on 18.12.2022.
//

#ifndef LAB3_3SEM_PRESENTER_H
#define LAB3_3SEM_PRESENTER_H

#include "../model/graph/Graph.h"

using namespace std;

template <typename T>
class Presenter {
private:
    Graph<T> graph;
    int size;
public:
    void generateGraph(int count);
    string topologicalSort();
    string connectivityComponents();
    string findShortestPaths();
    string findTheMinimumSkeleton();
    string printGraph();
};

#endif //LAB3_3SEM_PRESENTER_H
