#pragma once
#include "array.cpp"
#include "list.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
class ArrayStack : public List<T> {
protected:
    array<T> a;
    int n;

    // Dynamically grows or shrinks the array
    void resize() {
        array<T> b(std::max(1, 2 * n));
        array<T>::copy(a.a, 0, b.a, 0, n);
        
        // Safely swap the underlying pointers and lengths
        std::swap(a.a, b.a);
        std::swap(a.length, b.length);
    }

public:
    ArrayStack() : a(1), n(0) {}

    int size() override { 
        return n; 
    }

    T get(int i) override { 
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        return a.a[i]; 
    }

    T set(int i, T x) override {
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        T y = a.a[i];
        a.a[i] = x;
        return y;
    }

    void add(int i, T x) override {
        if (i < 0 || i > n) throw std::out_of_range("Index out of bounds");
        if (n + 1 > a.length) resize();
        
        // Shift elements to the right to make room
        for (int j = n; j > i; j--) {
            a.a[j] = a.a[j - 1];
        }
        a.a[i] = x;
        n++;
    }

    T remove(int i) override {
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        T x = a.a[i];
        
        // Shift elements to the left to fill the gap
        for (int j = i; j < n - 1; j++) {
            a.a[j] = a.a[j + 1];
        }
        n--;
        
        // Shrink the array if it is getting too empty
        if (a.length >= 3 * n) resize();
        return x;
    }

     // we only use these two methods for the benchmarking.
         
    void push(T x) { 
        add(n, x); // Adds to the very end (Top of stack)
    }
    
    T pop() { 
        if (n == 0) throw std::out_of_range("Stack is empty");
        return remove(n - 1); // Removes from the very end (Top of stack)
    }
};