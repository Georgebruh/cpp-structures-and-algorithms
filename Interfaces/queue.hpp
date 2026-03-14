#pragma once

template <typename T>
class Queue {
    public:
        virtual ~Queue() {}

        // Adds an element to the back of the queue
        virtual void enqueue(T data) = 0;

        // Removes and returns the element at the front of the queue
        virtual T dequeue() = 0;

        // Returns (without removing) the element at the front of the queue
        virtual T peek() const = 0;

        // Returns true if the queue contains no elements
        virtual bool isEmpty() const = 0;

        // Returns the number of elements currently in the queue
        virtual int size() const = 0;
};