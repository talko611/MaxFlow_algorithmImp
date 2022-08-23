//
// Created by Tal Koren on 22/08/2022.
//

#include <iostream>
#include "Graph.h"

int main(){
    Graph g = Graph();
    g.buildGraph();
    g.printGraph();
    g.removeEdge(1,2);
    g.removeEdge(5,4);
    g.removeEdge(6,5);
    g.printGraph();
}


