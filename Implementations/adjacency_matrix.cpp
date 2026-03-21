#pragma once
#include "../Interfaces/graph.hpp"
#include <vector>
#include <stdexcept>

class AdjacencyMatrix : public Graph {
protected:
    int numVertices;
    bool** matrix;

public:
    AdjacencyMatrix(int vertices) {
        numVertices = vertices;
        matrix = new bool*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            matrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++) {
                matrix[i][j] = false;
            }
        }
    }

    ~AdjacencyMatrix() override {
        for (int i = 0; i < numVertices; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void addEdge(int i, int j) override {
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            matrix[i][j] = true;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    void removeEdge(int i, int j) override {
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            matrix[i][j] = false;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    bool hasEdge(int i, int j) const override {
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            return matrix[i][j];
        }
        throw std::out_of_range("Index out of bounds");
    }

    std::vector<int> outEdges(int i) const override {
        std::vector<int> edges;
        if (i >= 0 && i < numVertices) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][j]) {
                    edges.push_back(j);
                }
            }
        } else {
            throw std::out_of_range("Index out of bounds");
        }
        return edges;
    }

    std::vector<int> inEdges(int i) const override {
        std::vector<int> edges;
        if (i >= 0 && i < numVertices) {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[j][i]) {
                    edges.push_back(j);
                }
            }
        } else {
            throw std::out_of_range("Index out of bounds");
        }
        return edges;
    }

    int getNumVertices() const override {
        return numVertices;
    }
};