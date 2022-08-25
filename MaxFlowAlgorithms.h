//
// Created by Tal Koren on 23/08/2022.
//

#pragma once
#include "Graph.h"
#include "FordFulkersonAnswer.h"
#include <queue>
#include <limits.h>

 class  MaxFlowAlgorithms {
    static bool bfs(Graph& residualGraph , std::vector<int>& parent, bool flag);

    static bool maxPathDijkstra(Graph& residualGraph, std::vector<int>& parent);

 public:
     static FordFulkersonAnswer fordFulkersonWithBfs(const Graph& g);

     static FordFulkersonAnswer fordFulkersonWithDijkstra(const Graph& g);

 };

