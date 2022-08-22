//
// Created by Tal Koren on 22/08/2022.
//
#include "Vertex.h"


std::ostream &operator<<(std::ostream &out, const Vertex &v) {
    out << "Id: " << v.id << " neighbours: ";
    std::for_each(v.edges.begin(), v.edges.end(), [&out](const Edge& e){out << e.getDest() << " ";});
    return out;
}
