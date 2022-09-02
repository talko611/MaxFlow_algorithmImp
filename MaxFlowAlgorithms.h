#pragma once
#include <queue>
#include <climits>
#include <utility>
#include "Graph.h"
#include "FordFulkersonAnswer.h"

class  MaxFlowAlgorithms {
    static bool bfs(Graph& residualGraph , std::vector<int>& parent, bool flag);

    static bool maxPathDijkstra(Graph& residualGraph, std::vector<int>& parent);

    static void getMinCut( FordFulkersonAnswer& answer, const std::vector<int>& parent, int sId);

    static int getFlowFromPath(Graph& residualGraph, std::vector<int>& parent);
public:
    static FordFulkersonAnswer fordFulkersonWithBfs(const Graph& g);

    static FordFulkersonAnswer fordFulkersonWithDijkstra(const Graph& g);
};