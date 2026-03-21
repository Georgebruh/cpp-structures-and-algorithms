#pragma once
#include "../Implementations/array_deque.cpp"
#include "../Interfaces/list.hpp"
#include <stdexcept>

template <typename T>
class ArrayDequeList : public ArrayDeque<T>, public List<T> {

public:

    // Constructor
    ArrayDequeList() : ArrayDeque<T>() {}

    // Core Operations


    T get(int i) const override {
        if (i < 0 || i >= this->count) {
            throw std::out_of_range("Index out of range.");
        }
        return this->a.a[(this->frontIndex + i) % this->a.length]; // circular index formula
    }

    T set(int i, T x) override {
        if (i < 0 || i >= this->count) {
            throw std::out_of_range("Index out of range.");
        }
        int idx = (this->frontIndex + i) % this->a.length; // circular index formula
        T old = this->a.a[idx];                            // save old value to return
        this->a.a[idx] = x;                                // overwrite with new value
        return old;
    }

    void add(int i, T x) override {
        if (i < 0 || i > this->count) {
            throw std::out_of_range("Index out of range.");
        }

        if (i < this->count / 2) {
            // shift left half left by one — move frontIndex back
            this->addFirst(x);                             // make room at front
            for (int j = 0; j < i; j++) {                 // shift elements forward to index i
                this->a.a[(this->frontIndex + j) % this->a.length] =
                    this->a.a[(this->frontIndex + j + 1) % this->a.length];
            }
            this->a.a[(this->frontIndex + i) % this->a.length] = x; // place x at index i
        } else {
            // shift right half right by one — move rear forward
            this->addLast(x);                              // make room at back
            for (int j = this->count - 1; j > i; j--) {  // shift elements backward to index i
                this->a.a[(this->frontIndex + j) % this->a.length] =
                    this->a.a[(this->frontIndex + j - 1) % this->a.length];
            }
            this->a.a[(this->frontIndex + i) % this->a.length] = x; // place x at index i
        }
    }

    T remove(int i) override {
        if (i < 0 || i >= this->count) {
            throw std::out_of_range("Index out of range.");
        }

        T val = this->a.a[(this->frontIndex + i) % this->a.length]; // save value to return

        if (i < this->count / 2) {
            // shift left half right by one — move frontIndex forward
            for (int j = i; j > 0; j--) {                // shift elements backward to close gap
                this->a.a[(this->frontIndex + j) % this->a.length] =
                    this->a.a[(this->frontIndex + j - 1) % this->a.length];
            }
            this->removeFirst();                           // remove the now-duplicate front
        } else {
            // shift right half left by one — move rear backward
            for (int j = i; j < this->count - 1; j++) {  // shift elements forward to close gap
                this->a.a[(this->frontIndex + j) % this->a.length] =
                    this->a.a[(this->frontIndex + j + 1) % this->a.length];
            }
            this->removeLast();                            // remove the now-duplicate back
        }

        return val;
    }

    int size() const override {
        return this->count;
    }
};