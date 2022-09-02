#include "Vertex.h"


std::ostream &operator<<(std::ostream &out, const Vertex &v) {
    out << "Id: " << v.id << " neighbours: ";
    for(const Edge& temp : v.edges){
        out << temp.getDest() << " ";
    }
    return out;
}