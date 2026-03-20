#pragma once

template <typename T>
struct HashNode {
    T value;
    HashNode* next;

    HashNode(T val) : value(val), next(nullptr) {}
};