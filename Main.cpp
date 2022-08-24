//
// Created by Tal Koren on 22/08/2022.
//

#include <iostream>
#include "Graph.h"
#include "MaxFlowAlgorithms.h"

void printResult(FordFulkersonAnswer& answer ,  std::string&& type);

int main(){
    Graph g = Graph();
    g.buildGraph();
//    g.printGraph();
    FordFulkersonAnswer answer = MaxFlowAlgorithms::fordFulkersonWithBfs(g);
    printResult(answer, "BFS");
}

void printResult(FordFulkersonAnswer& answer ,  std::string&& type){
    std::cout << type << " Method:" << std::endl;
    std::cout<< "Max flow = " << answer.getMaxFlow() << std::endl;
    std::cout << "Min cut: S: ";

    int size = answer.getLeft().size();
    for(int i = 0; i < size; ++i){
        if(i == size -1){
            std::cout << answer.getLeft()[i] << ".";
        } else{
            std::cout << answer.getLeft()[i] << ", ";
        }
    }
    std::cout << " T:";
    size = answer.getRight().size();
    for(int i = 0; i < size; ++i){
        if(i == size -1){
            std::cout << answer.getRight()[i] << ".";
        } else{
            std::cout << answer.getRight()[i] << ", ";
        }
    }
}


