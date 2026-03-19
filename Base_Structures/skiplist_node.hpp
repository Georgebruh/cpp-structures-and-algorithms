#pragma once
#include <vector>

template <typename T>
struct SkiplistNode {
    T value;

    std::vector<SkiplistNode<T>*> next;         // array of next pointers, one per level

    SkiplistNode(T value, int height) : value(value), next(height, nullptr) {}

    int height() const {
        return next.size();
    }
};  