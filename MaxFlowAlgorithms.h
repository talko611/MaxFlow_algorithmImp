//
// Created by Tal Koren on 23/08/2022.
//

#pragma once
#include "Graph.h"
#include "FordFulkersonAnswer.h"
#include <queue>

 class  MaxFlowAlgorithms {
    static bool bfs(Graph& residualGraph , std::vector<int>& parent, bool flag);

 public:
     static FordFulkersonAnswer fordFulkersonWithBfs(const Graph& g);
 };

