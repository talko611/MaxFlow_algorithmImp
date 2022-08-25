//
// Created by Tal Koren on 22/08/2022.
//

#pragma once
#include <iostream>
#include <algorithm>
#include "Vertex.h"
#include <vector>


class Graph{
private:
    std::vector<Vertex> vertexes;
    Vertex* s = nullptr;
    Vertex* t = nullptr;

public:
    Graph(){}

    Graph(const Graph& copyFrom){

        this->makeEmptyGraph(copyFrom.getVertexesSize());

        for(const Vertex& v : copyFrom.vertexes){
            for(const Edge& e : v.getEdges()){
                this->addEdge(e.getSrc(), e.getDest(), e.getCapacity());
            }
        }
        this->s = &this->vertexes[copyFrom.s->getId() -1];
        this->t = &this->vertexes[copyFrom.t->getId() -1];

    }
    void makeEmptyGraph(int numOfVertexes);

    std::list<int> getAdjList(int vertexId);

    void addEdge(int src, int dest, int weight);

    void removeEdge(int src, int dest);

    int getVertexesSize()const{return this->vertexes.size();}

    const Vertex& getS() const;

    Vertex& getS(){return *s;}

    const Vertex& getT() const;

    const Vertex& getVertexById(int id) const{
        return vertexes[id -1];
    }

    Edge* getEdge(int src, int dest);

    void printGraph();

    void buildGraph();

};
