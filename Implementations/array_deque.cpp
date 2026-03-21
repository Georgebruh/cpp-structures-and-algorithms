#pragma once
#include "../Base_Structures/array.cpp"
#include "../Interfaces/deque.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
class ArrayDeque : public Deque<T> {
protected:
    array<T> a;
    int frontIndex;
    int count;

    // Dynamically grows or shrinks the array
    void resize() {
        array<T> b(std::max(1, 2 * count));
        for (int i = 0; i < count; i++) {
            b.a[i] = a.a[(frontIndex + i) % a.length];
        }
        
        // Safely swap the underlying pointers and lengths
        std::swap(a.a, b.a);
        std::swap(a.length, b.length);
        frontIndex = 0;
    }

public:
    ArrayDeque() : a(8), frontIndex(0), count(0) {}

    void addFirst(T x) override {
        if (count == a.length) resize();
        frontIndex = (frontIndex - 1 + a.length) % a.length;
        a.a[frontIndex] = x;
        count++;
    }

    void addLast(T x) override {
        if (count == a.length) resize();
        int rearIndex = (frontIndex + count) % a.length;
        a.a[rearIndex] = x;
        count++;
    }

    T removeFirst() override {
        if (count == 0) throw std::out_of_range("Deque is empty");
        T removed = a.a[frontIndex];
        frontIndex = (frontIndex + 1) % a.length;
        count--;
        
        // Shrink the array if it is getting too empty
        if (a.length >= 3 * count && count > 0) resize();
        return removed;
    }

    T removeLast() override {
        if (count == 0) throw std::out_of_range("Deque is empty");
        int rearIndex = (frontIndex + count - 1) % a.length;
        T removed = a.a[rearIndex];
        count--;
        
        // Shrink the array if it is getting too empty
        if (a.length >= 3 * count && count > 0) resize();
        return removed;
    }

    int size() const override {
        return count;
    }
};