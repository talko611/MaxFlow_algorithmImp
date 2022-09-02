#include "MaxFlowAlgorithms.h"

bool MaxFlowAlgorithms::bfs(Graph& residualGraph , std::vector<int>& parent, bool stopAtT){
    //Init
    std::queue<const Vertex*> queue;
    std::vector<bool> visited(residualGraph.getVertexesSize(), false);
    const Vertex& s = residualGraph.getS();
    const Vertex& t = residualGraph.getT();
    queue.push(&s);
    parent[s.getId() -1] = -1;
    visited[s.getId() -1] = true;
    const Vertex* current = nullptr;

    //Main loop
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

bool MaxFlowAlgorithms::maxPathDijkstra(Graph &residualGraph, std::vector<int> &parent) {
    //init
    auto comp = [](const std::pair<int, int> v1, const std::pair<int, int >v2){return v1.second < v2.second;};
    std::priority_queue<std::pair<int , int>, std::vector<std::pair<int, int>>, decltype(comp)> queue(comp);
    std::vector<int> weight(residualGraph.getVertexesSize(), std::numeric_limits<int>::min());

    weight[residualGraph.getS().getId() -1] = std::numeric_limits<int>::max();
    queue.push(std::make_pair(residualGraph.getS().getId(), std::numeric_limits<int>::max()));
    const Vertex* currentVertex;
    std::pair<int, int> current;
    int dest;
    int flowCanPass;
    //Main loop
    while(!queue.empty()){
        current = queue.top();
        currentVertex = &residualGraph.getVertexById(current.first);
        queue.pop();
        for(const Edge& e : currentVertex->getEdges()){
            if(e.getCapacity() != 0){
                dest = e.getDest();
                flowCanPass = std::min(current.second, e.getCapacity());
                if(weight[dest - 1] < flowCanPass){
                    weight[dest - 1] = flowCanPass;
                    parent[dest -1] = current.first -1;
                    queue.push(std::make_pair(dest, flowCanPass));
                }
            }
        }
    }
    return parent[residualGraph.getT().getId() -1] != -1;
}

FordFulkersonAnswer MaxFlowAlgorithms::fordFulkersonWithBfs(const Graph& g){
    Graph residualGraph = Graph(g);
    FordFulkersonAnswer answer;
    std::vector<int> parent(g.getVertexesSize(), -1);
    int maxFlow = 0;

    while(bfs(residualGraph, parent, true )){
        maxFlow += getFlowFromPath(residualGraph, parent);
    }
    std::fill(parent.begin(), parent.end(), -1);
    bfs(residualGraph,parent, false);
    getMinCut(answer, parent, residualGraph.getS().getId());
    answer.setMaxFlow(maxFlow);
    return answer;
}

FordFulkersonAnswer MaxFlowAlgorithms::fordFulkersonWithDijkstra(const Graph &g) {
    Graph residualGraph = Graph(g);
    FordFulkersonAnswer answer;
    std::vector<int> parent(g.getVertexesSize(), -1);
    int maxFlow = 0;

    while (maxPathDijkstra(residualGraph, parent)){
        maxFlow += getFlowFromPath(residualGraph, parent);
        for(int i = 0; i < parent.size(); ++i)
            parent[i] = -1;
    }
    std::fill(parent.begin(), parent.end(), -1);
    bfs(residualGraph,parent, false);
    getMinCut(answer, parent, residualGraph.getS().getId());
    answer.setMaxFlow(maxFlow);
    return answer;
}

int MaxFlowAlgorithms::getFlowFromPath(Graph& residualGraph, std::vector<int>& parent){
    int currentVertex;
    int tId = residualGraph.getT().getId();
    int sId = residualGraph.getS().getId();
    int flowOnPath = std::numeric_limits<int>::max();
    for(int i = tId -1; i != sId -1; i = parent[i] ){
        currentVertex = parent[i];
        flowOnPath = std::min(flowOnPath, (residualGraph.getEdge(currentVertex + 1, i + 1)->getCapacity()));
    }

    for(int i = tId -1 ; i!= sId -1; i = parent[i]){
        currentVertex = parent[i];
        Edge* e1 = residualGraph.getEdge(currentVertex + 1, i + 1);
        e1->setCapacity(e1->getCapacity() - flowOnPath);
        if(residualGraph.getEdge(i + 1, currentVertex + 1) != nullptr){
            Edge& e2 = *residualGraph.getEdge(i + 1, currentVertex + 1);
            e2.setCapacity(e2.getCapacity() + flowOnPath);
        }
        else{
            residualGraph.addEdge(i + 1, currentVertex + 1, flowOnPath);
        }
    }
    return flowOnPath;
}

void MaxFlowAlgorithms::getMinCut(FordFulkersonAnswer &answer, const std::vector<int> &parent, int sId) {
    for(int i = 0 ; i < parent.size(); ++i){
        if(i +1 == sId){
            answer.addVertexToLeft(sId);
        }
        else if(parent[i] == -1){
            answer.addVertexToRight(i +1);
        }
        else{
            answer.addVertexToLeft(i + 1);
        }
    }
}