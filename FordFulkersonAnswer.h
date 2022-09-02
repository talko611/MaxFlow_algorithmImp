#pragma once
#include <vector>


class FordFulkersonAnswer {
private:
    std::vector<int> left, right;
    int maxFlow;

public:
    std::vector<int>& getLeft(){return this->left;}

    std::vector<int>& getRight(){return this->right;}

    int getMaxFlow(){return this->maxFlow;}

    void addVertexToRight(int vertexId){ this->right.push_back(vertexId);}

    void addVertexToLeft(int vertexId){ this->left.push_back(vertexId);}

    void setMaxFlow(int maxFlow){this->maxFlow = maxFlow;}
};