#pragma once

template <typename T>
struct DLLNode {
    T value;            // value stored in this node

    DLLNode<T>* prev;   // pointer to the previous node in the chain
    DLLNode<T>* next;   // pointer to the next node in the chain

    // constructor to initialize them
    DLLNode(T value) : value(value), prev(nullptr), next(nullptr) {}
};