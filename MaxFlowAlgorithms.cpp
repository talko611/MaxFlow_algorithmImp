
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

bool MaxFlowAlgorithms::maxPathDijkstra(Graph &residualGraph, std::vector<int> &parent) {
    auto cmp = [](const Edge* e1, const Edge* e2){return e1->getCapacity() < e2->getCapacity();};
    std::priority_queue<const Edge*, std::vector<const Edge*>, decltype( cmp)> priorityQueue(cmp);
    std::vector<bool> visited(residualGraph.getVertexesSize(), false);
    const Vertex& s = residualGraph.getS();
    const Vertex& t = residualGraph.getT();
    auto addEdgesToQueue = [&priorityQueue](const Edge& e){
        if(e.getCapacity() > 0)
            priorityQueue.push(&e);
    };
//    for(const Edge& temp : s.getEdges()){
//        if(temp.getCapacity()>0){
//            priorityQueue.push(&temp);
//        }
//    }
    std::for_each(s.getEdges().begin(), s.getEdges().end(), addEdgesToQueue);
    visited[s.getId() -1] = true;
    parent[s.getId() -1] = -1;

    const Vertex* currVertex = &s;
    const Edge* currenEdge = nullptr;

    while(!priorityQueue.empty()){
        currenEdge = priorityQueue.top();
        priorityQueue.pop();
        if(!visited[currenEdge->getDest() -1]){
            currVertex = &residualGraph.getVertexById(currenEdge->getDest());
            if(currVertex->getId() == t.getId()){
                parent[t.getId() -1] = currenEdge->getSrc() -1;
                return true;
            }
            std::for_each(currVertex->getEdges().begin(), currVertex->getEdges().end(), addEdgesToQueue);
//            for(const Edge& temp : currVertex->getEdges()){
//                if(temp.getCapacity()>0){
//                    priorityQueue.push(&temp);
//                }
//            }
            visited[currVertex->getId() -1] = true;
            parent[currVertex->getId() -1] = currenEdge->getSrc() -1;
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
        flowOnPath = std::numeric_limits<int>::max();
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

FordFulkersonAnswer MaxFlowAlgorithms::fordFulkersonWithDijkstra(const Graph &g) {
    Graph residualGraph = Graph(g);
    FordFulkersonAnswer answer;
    std::vector<int> parent(g.getVertexesSize(), -1);
    int maxFlow = 0;
    int tId = g.getT().getId();
    int sId = g.getS().getId();
    int flowOnPath;
    int currentVertex;

    while (maxPathDijkstra(residualGraph, parent)){
        flowOnPath = std::numeric_limits<int>::max();
        for(int i = tId -1; i != sId -1; i = parent[i] ){
            currentVertex = parent[i];
            flowOnPath = std::min(flowOnPath, (residualGraph.getEdge(currentVertex + 1, i + 1))->getCapacity());
        }

        for(int i = tId -1 ; i!= sId -1; i = parent[i]){
            currentVertex = parent[i];
            Edge& e1 = *residualGraph.getEdge(currentVertex + 1, i + 1);
            e1.setCapacity(e1.getCapacity() - flowOnPath);
            if(residualGraph.getEdge(i + 1, currentVertex + 1) != nullptr){
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
