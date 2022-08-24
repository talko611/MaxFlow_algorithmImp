
#include "MaxFlowAlgorithms.h"

 bool MaxFlowAlgorithms::bfs(Graph& residualGraph , std::vector<int>& parent, bool stopAtT){
    std::queue<const Vertex*> queue;
    std::vector<bool> visited(residualGraph.getVertexesSize(), false);
     const Vertex& s = residualGraph.getS();
     const Vertex& t = residualGraph.getT();

    queue.push(&s);
    parent[s.getId() -1] = -1;
    visited[s.getId() -1] = true;
    const Vertex* current = nullptr;

    while(!queue.empty()){
        current = queue.front();
        queue.pop();
        const std::list<Edge>& edges = current->getEdges();
        for(const Edge& edge : edges){
            if(!visited[edge.getDest() -1] && edge.getCapacity() > 0){
                if(edge.getDest() == t.getId() && stopAtT){
                    parent[t.getId() -1] = current->getId() -1;
                    return true;//return because function looks for the first time to find a path to t
                }
                queue.push(&residualGraph.getVertexById(edge.getDest()));
                visited[edge.getDest() -1] = true;
                parent[edge.getDest() -1] = current->getId() -1;
            }
        }
    }
    return false;
}

FordFulkersonAnswer MaxFlowAlgorithms::fordFulkersonWithBfs(const Graph& g){
    Graph residualGraph = Graph(g);
    FordFulkersonAnswer answer;
    std::vector<int> parent(g.getVertexesSize(), -1);
    int maxFlow = 0;
    int tId = g.getT().getId();
    int sId = g.getS().getId();
    int flowOnPath;
    int currentVertex;
    while(bfs(residualGraph, parent, true )){
        flowOnPath = INT_MAX;
        for(int i = tId -1; i != sId -1; i = parent[i] ){
            currentVertex = parent[i];
            flowOnPath = std::min(flowOnPath, (residualGraph.getEdge(currentVertex + 1, i + 1))->getCapacity());
        }

        for(int i = tId -1 ; i!= sId -1; i = parent[i]){
            currentVertex = parent[i];
            Edge& e1 = *residualGraph.getEdge(currentVertex + 1, i + 1);
            e1.setCapacity(e1.getCapacity() - flowOnPath);
            if(residualGraph.getVertexById(i + 1).getEdges().end() != residualGraph.getEdge(i + 1, currentVertex + 1)){
                Edge& e2 = *residualGraph.getEdge(i + 1, currentVertex + 1);
                e2.setCapacity(e2.getCapacity() + flowOnPath);
            }
            else{
                residualGraph.addEdge(i + 1, currentVertex + 1, flowOnPath);
            }
        }
        maxFlow += flowOnPath;
    }
    std::fill(parent.begin(), parent.end(), -1);
    bfs(residualGraph,parent, false);
    answer.addVertexToLeft(sId);
    for(int i = 1 ; i < parent.size(); ++i){
        if(parent[i] == -1){
            answer.addVertexToRight(i +1);
        }
        else{
            answer.addVertexToLeft(i + 1);
        }
    }
    answer.setMaxFlow(maxFlow);
    return answer;
}