#pragma once
// A generic node for a SLList
// Holds a value and a pointer to the next node

template <typename T>
struct SLLNode {
    T value;                    // the value stored in this node
    SLLNode<T>* next;           // pointer to the next node in the chain
    
    // constructor to initialize them
    SLLNode(T value) : value(value), next(nullptr) {}
};