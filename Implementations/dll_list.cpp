#pragma once
#include "../Interfaces/list.hpp"
#include "../Base_Structures/dll_node.hpp"
#include <stdexcept>

template <typename T>
class DLList : public List<T> {

private:
    DLLNode<T>* dummy;      // sentinel head node, holds no real data
    int n;                  // number of elements in the list

    DLLNode<T>* getNode(int i) const {
        DLLNode<T>* current;

        if (i < n/2) {
            // traverse forward from dummy->next (head)
            current = dummy->next;
            for (int j = 0; j < i; j++) {
                current = current->next;
            }
        } else {
            // traverse backward from the last node
            current = dummy;
            for (int j = n; j > i; j--) {
                current = current->prev;
            }
        }

        return current;
    }

    void addBefore(DLLNode<T>* u, DLLNode<T>* w) {
        w->prev = u->prev;  // w's prev points to u's old prev
        w->next = u;        // w's next points to u
        w->prev->next = w;  // u's old prev now points forward to w
        u->prev = w;        // u's prev now points back to w
        n++;
    }

    void removeNode(DLLNode<T>* u) {
        u->prev->next = u->next;  // skip over u going forward
        u->next->prev = u->prev;  // skip over u going backward
        delete u;                 // free the node's memory
        n--;
    }

public:
    DLList() : n(0) {
        dummy = new DLLNode<T>(T());  // dummy node with default value
        dummy->next = dummy;          // points to itself (empty list)
        dummy->prev = dummy;          // points to itself (empty list)
    }

    ~DLList() {
        DLLNode<T>* current = dummy->next;  // start from first real node
        while (current != dummy) {          // stop when we loop back to dummy
            DLLNode<T>* next = current->next;
            delete current;
            current = next;
        }
        delete dummy;                       // finally delete the dummy node
    }

    T get(int i) const override {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range.");
        }
        return getNode(i)->value;   // traverse to node at i, return its value
    }
    
    T set(int i, T x) override {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range.");
        }
        DLLNode<T>* u = getNode(i); // traverse to node at i
        T old = u->value;           // save the old value to return
        u->value = x;               // overwrite with new value
        return old;
    }

    void add(int i, T x) override {
        if (i < 0 || i > n) {
            throw std::out_of_range("Index out of range.");
        }
        DLLNode<T>* newNode = new DLLNode<T>(x); // create new node
        addBefore(getNode(i), newNode);           // insert before node at i
    }

    T remove(int i) override {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range.");
        }
        DLLNode<T>* u = getNode(i); // traverse to node at i
        T val = u->value;           // save value to return
        removeNode(u);              // unlink and delete the node
        return val;
    }

    int size() const override {
        return n;
    }
};

