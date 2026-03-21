#pragma once
#include <vector>

class Graph {
public:
    virtual ~Graph() {}
    
    virtual void addEdge(int i, int j) = 0;
    virtual void removeEdge(int i, int j) = 0;
    virtual bool hasEdge(int i, int j) const = 0;
    virtual std::vector<int> outEdges(int i) const = 0;
    virtual std::vector<int> inEdges(int i) const = 0;
    virtual int getNumVertices() const = 0;
};