#pragma once

template <typename T>
struct BTNode {
    T data;
    BTNode* left;
    BTNode* right;
    
    BTNode(T val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};