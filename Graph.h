//
// Created by Tal Koren on 22/08/2022.
//

#pragma once
#include <iostream>
#include "Vertex.h"
#include <vector>


class Graph{
private:
    std::vector<Vertex> vertexes;
    Vertex* s;
    Vertex* t;

public:
    void printGraph();
    bool buildGraph();
};
