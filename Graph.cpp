#include "Graph.h"

void Graph::printGraph() {
    std::for_each(vertexes.begin(), vertexes.end(), [](const Vertex& vertex){
        std::cout << vertex << std::endl;
    });
    std::cout << "S: " << s->getId()<< std::endl;
    std::cout << "T: " << t->getId()<< std::endl;
}

bool Graph::buildGraph() {
    int vertexesNum, edgesNum, sId, tId;
    std::cout << "num of vertexes:\n";
    std::cin >> vertexesNum;
    std::cout << "num of edges:\n";
    std::cin >> edgesNum;
    std::cout << "num of s:\n";
    std::cin >> sId;
    std::cout << "num of t:\n";
    std::cin >> tId;

    this->vertexes = std::vector<Vertex>(vertexesNum);
    for (int i = 0; i < vertexesNum; ++i)vertexes[i].setId(i + 1);
    this->s = &vertexes[sId -1];
    this->t = &vertexes[tId -1];
    int src, dest, weight;
    for(int i = 0; i< edgesNum; ++i){
        std::cin >> src >> dest >> weight;
        vertexes[src - 1].getEdges().emplace_back(src, dest, weight);
    }
    return true;
}

