#pragma once

template <typename T>
class Deque {
    public:
        virtual ~Deque() {}

        virtual void addFirst(T x) = 0; // Adds an element to the front of the deque
        virtual void addLast(T x) = 0;  // Adds an element to the back of the deque
        virtual T removeFirst() = 0;    // Removes and returns the element at the front of the deque
        virtual T removeLast() = 0;     // Removes and returns the element at the back of the deque
        virtual int size() const = 0;   // Returns the number of elements currently in the deque
};