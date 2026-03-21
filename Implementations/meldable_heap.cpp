#pragma once
#include <vector>
#include <stdexcept>
#include <cstdlib> // For rand()
#include "../Interfaces/queue.hpp"
#include "../Base_Structures/bt_node.hpp"

template <typename T>
class MeldableHeap : public Queue<T> {
private:
    BTNode<T>* root;
    int n;

    // The core function: Merges two heaps into one valid Max-Heap
    BTNode<T>* meld(BTNode<T>* h1, BTNode<T>* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        
        // Max-Heap property: the larger value must be the parent
        if (h1->data < h2->data) {
            BTNode<T>* temp = h1;
            h1 = h2;
            h2 = temp;
        }
        
        // Randomly merge the smaller tree into the left or right child.
        // This "coin flip" prevents the tree from becoming wildly unbalanced.
        if (std::rand() % 2 == 0) {
            h1->left = meld(h1->left, h2);
        } else {
            h1->right = meld(h1->right, h2);
        }
        
        return h1;
    }

   // Helper to iteratively delete nodes and prevent memory leaks
    void destroyTree(BTNode<T>* node) {
        if (node == nullptr) return;
        
        std::vector<BTNode<T>*> stack;
        stack.push_back(node);
        
        while (!stack.empty()) {
            BTNode<T>* current = stack.back();
            stack.pop_back();
            
            if (current->left != nullptr) {
                stack.push_back(current->left);
            }
            if (current->right != nullptr) {
                stack.push_back(current->right);
            }
            
            delete current;
        }
    }

public:
    MeldableHeap() : root(nullptr), n(0) {}
    
    ~MeldableHeap() override {
        destroyTree(root);
    }

    void enqueue(T data) override {
        BTNode<T>* newNode = new BTNode<T>(data);
        root = meld(root, newNode); // Melding the current heap with a 1-node heap
        n++;
    }

    T dequeue() override {
        if (n == 0) throw std::out_of_range("Queue is empty");
        
        T extractedData = root->data;
        BTNode<T>* oldRoot = root;
        
        // The new heap is simply the left and right subtrees melded together
        root = meld(root->left, root->right);
        
        delete oldRoot;
        n--;
        
        return extractedData;
    }

    T peek() const override {
        if (n == 0) throw std::out_of_range("Queue is empty");
        return root->data;
    }

    bool isEmpty() const override { return n == 0; }
    
    int size() const override { return n; }
};