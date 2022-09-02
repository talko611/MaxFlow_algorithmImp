#pragma once

class Edge {
private:
    int srcId;
    int destId;
    int capacity;

public:
    Edge(int src, int dest, int weight) : srcId(src), destId(dest), capacity(weight){};

    int getSrc() const {
        return srcId;
    }

    int getDest() const {
        return destId;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int capacity){
        this->capacity = capacity;
    }

    bool operator==(const Edge& e) const{
        return e.srcId == this->srcId && e.destId == this->destId;
    }

    friend std::ostream & operator <<(std::ostream& out, const Edge& e){
        return out << "src: " << e.srcId << " dest: " << e.destId << " weight: " << e.capacity;
    }
};