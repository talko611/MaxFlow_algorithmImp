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
    std::cin >> vertexesNum;
    std::cin >> edgesNum;
    std::cin >> sId;
    std::cin >> tId;
    validateInput(vertexesNum, edgesNum, sId, tId);

    makeEmptyGraph(vertexesNum);
    this->s = &vertexes[sId -1];
    this->t = &vertexes[tId -1];
    int src, dest, weight;
    for(int i = 0; i< edgesNum; ++i){
        std::cin >> src >> dest >> weight;
        if(src <= 0 || src > vertexesNum || dest <= 0 || dest > vertexesNum || weight < 0)
            throw std::invalid_argument("invalid input");
        addEdge(src, dest,weight);
    }
}

void Graph::validateInput(int numOfVertexes, int numOfEdges, int sId, int tId) {
    if(numOfVertexes <= 0)
        throw std::invalid_argument("invalid input");
    if(numOfEdges <= 0 )
        throw std::invalid_argument("invalid input");
    if(sId <=0 || sId > numOfVertexes || tId <= 0 || tId > numOfVertexes)
        throw std::invalid_argument("invalid input");
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
    if(found != this->vertexes[src -1].getEdges().end())
        edges.remove(*found);
}

const Vertex& Graph::getS() const {
    return *s;
}

const Vertex& Graph::getT() const {
    return *t;
}

Edge* Graph::getEdge(int src, int dest) {
    Edge e(src,dest,0);
    std::list<Edge>& refLst = this->vertexes[src -1].getEdges();
    auto res = std::find_if(refLst.begin(), refLst.end() ,[&src, &dest](const Edge& edge){
        return edge.getSrc() == src && edge.getDest() == dest;
    });

    return (res == refLst.end()) ? nullptr : &(*res);
}

std::vector<Vertex> &Graph::getVertexes()  {
    return vertexes;
}