//
// Created by Tal Koren on 22/08/2022.
//

#pragma once

class Edge {
private:
    int srcId;
    int destId;
    int weight;

public:
    Edge(int src, int dest, int weight) : srcId(src), destId(dest),weight(weight){};

    int getSrc() const {
        return srcId;
    }

    int getDest() const {
        return destId;
    }

    int getWeight() const {
        return weight;
    }
};

