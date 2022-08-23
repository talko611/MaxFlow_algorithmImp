#include "Graph.h"

void Graph::printGraph() {
    std::for_each(vertexes.begin(), vertexes.end(), [](const Vertex& vertex){
        std::cout << vertex << std::endl;
    });
    std::cout << "S: " << s->getId()<< std::endl;
    std::cout << "T: " << t->getId()<< std::endl;
}

void Graph::buildGraph() {
    int vertexesNum, edgesNum, sId, tId;
    std::cout << "num of vertexes:\n";
    std::cin >> vertexesNum;
    std::cout << "num of edges:\n";
    std::cin >> edgesNum;
    std::cout << "num of s:\n";
    std::cin >> sId;
    std::cout << "num of t:\n";
    std::cin >> tId;

    makeEmptyGraph(vertexesNum);
    this->s = &vertexes[sId -1];
    this->t = &vertexes[tId -1];
    int src, dest, weight;
    for(int i = 0; i< edgesNum; ++i){
        std::cin >> src >> dest >> weight;
        addEdge(src, dest,weight);
    }
}

void Graph::makeEmptyGraph(int numOfVertexes) {
    for(int i = 0; i < numOfVertexes; ++i){
        this->vertexes.emplace_back(i + 1);
    }
}

std::list<int> Graph::getAdjList(int vertexId) {
    std::list<int> adjLst;
    const std::list<Edge>& vertexNeighbours = this->vertexes[vertexId].getEdges();
    std::for_each(vertexNeighbours.begin(), vertexNeighbours.end(), [&adjLst](const Edge& e){
        adjLst.push_back(e.getDest());
    });
    return adjLst;
}

void Graph::addEdge(int src, int dest, int weight) {
    this->vertexes[src -1].addEdge(dest,weight);
}

void Graph::removeEdge(int src, int dest) {
    std::list<Edge>& edges = this->vertexes[src -1].getEdges();
    auto found = (std::find_if(edges.begin(), edges.end(), [&src, &dest](const Edge& e){
        return e.getSrc() == src && e.getDest() == dest;
    }));
    edges.remove(*found);
}

const Vertex& Graph::getS() const {
    return *s;
}

const Vertex& Graph::getT() const {
    return *t;
}

