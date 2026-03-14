#pragma once
#include "../Base_Structures/sll_node.hpp"
#include "../Interfaces/queue.hpp"
#include <stdexcept>

template <typename T>
class SLLQueue : public Queue<T> {

private:
    SLLNode<T>* head;  // points to the front of the queue
    SLLNode<T>* tail;  // points to the back of the queue
    int count;         // number of elements in the queue

public:
    // initializes an empty queue with no nodes
    SLLQueue() : head(nullptr), tail(nullptr), count(0) {}

    ~SLLQueue() {
        while(!isEmpty()) {
            dequeue();
        }
    }

    // creates a new node and appends it to the tail
    // if the queue was empty, both head and tail point to the new node
    // otherwise, the current tail links to the new node and tail advances
    void enqueue(T data) override {
        SLLNode<T>* newNode = new SLLNode<T>(data);

        if(isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        count++;
    }

    // saves the head's value, advances head forward, then deletes the old head
    // if the queue becomes empty after removal, tail is also nulled out
    T dequeue() override {
        if(isEmpty()) {
            throw std::underflow_error("Queue is empty. Cannot dequeue.");
        }

        SLLNode<T>* temp = head;        // hold old head so we can delete it after
        T data = head->value;           // save the value to return
        head = head->next;              // advance head to the next node

        if(head == nullptr) {           // queue is now empty, clean up tail too
            tail = nullptr;
        }

        delete temp;                    // free the old head node
        count--;
        return data;
    }

    // returns the front value w/o modifying the queue
    T peek() const override {
        if(isEmpty()) {
            throw std::underflow_error("Queue is empty. Cannot peek.");
        }
        return head->value;
    }

    // means no nodes exist in the queue
    bool isEmpty() const override {
        return count == 0;
    }

    // returns the tracked count directly
    int size() const override {
        return count;
    }
};