
#include "MaxFlowAlgorithms.h"

static bool bfs(Graph residualGraph , int parent[]){
    std::queue<Vertex> queue;
    std::vector<bool> visited(residualGraph.getVertexesSize(), false);
    const Vertex& s = residualGraph.getS();
    const Vertex& t = residualGraph.getT();

    queue.push(residualGraph.getS());
    parent[s.getId() -1] = -1;
    visited[s.getId() -1] = true;
    Vertex* current;

    while(!queue.empty()){
        *current = queue.front();
        queue.pop();
        std::list<Edge> edges = current->getEdges();
        for(const Edge& edge : edges){
            if(!visited[edge.getDest() -1] && edge.getFlow() > 0){
                if(edge.getDest() == t.getId()){
                    parent[t.getId() -1] = current->getId();
                    return true;//return because function looks for the first time to find a path to t
                }
                queue.push(residualGraph.getVertexById(edge.getDest()));
                visited[edge.getDest() -1] = true;
                parent[edge.getDest() -1] = current->getId();
            }
        }
    }
    return false;
}