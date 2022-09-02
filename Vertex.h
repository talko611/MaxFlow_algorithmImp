#pragma once
#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include "Edge.h"

class Vertex {
private:
    int id;
    std::list<Edge> edges;

public:
    Vertex(int id) :id(id){}

    int getId() const {
        return id;
    }

    std::list<Edge> &getEdges() {
        return edges;
    }

    const std::list<Edge> &getEdges() const {
        return edges;
    }

    void setId(int id){this->id = id;}

    void addEdge(int dest, int weight){
        edges.emplace_back(this->id, dest, weight);
    }

    friend std::ostream & operator<<(std::ostream& out, const Vertex& v);
};
