//
// Created by Tal Koren on 22/08/2022.
//

#pragma once
#include <list>
#include <utility>
#include <iostream>
#include "Edge.h"

class Vertex {
private:
    int id;
    std::list<Edge> edges;

public:
//    Vertex(int id, std::list<Edge>& edges): id(id), edges(edges){}

    int getId() const {
        return id;
    }

    std::list<Edge> &getEdges() {
        return edges;
    }
    void setId(int id){this->id = id;}

    friend std::ostream & operator<<(std::ostream& out, const Vertex& v);
};



