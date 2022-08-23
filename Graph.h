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
    void makeEmptyGraph(int numOfVertexes);

    std::list<int> getAdjList(int vertexId);

    void addEdge(int src, int dest, int weight);

    void removeEdge(int src, int dest);

    int getVertexesSize()const{return vertexes.size();}

    const Vertex& getS() const;

    const Vertex& getT() const;

    const Vertex& getVertexById(int id) const{
        return vertexes[id -1];
    }

    void printGraph();
    void buildGraph();
};
