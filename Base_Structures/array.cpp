#pragma once
#include <algorithm>

template <typename T>
struct array {
    T* a;
    int length;

    array(int len) {
        length = len;
        a = new T[length];
    }

    ~array() {
        delete[] a;
    }

    // Helper to easily copy elements when resizing
    static void copy(T* src, int src_pos, T* dest, int dest_pos, int len) {
        std::copy(src + src_pos, src + src_pos + len, dest + dest_pos);
    }
};