#pragma once
#include "../Interfaces/sset.hpp"
#include "../Base_Structures/hash_node.hpp"
#include <vector>
#include <functional>

template <typename T>
class ChainedHashSet : public SSet<T> {
    private:
        std::vector<HashNode<T>*> table;           // The hash table array (buckets)
        int n;                                     // number of elements in the set
        int capacity;                              // current size of the table

        // Utility to compute the hash index
        size_t hash(T x) const {
            return std::hash<T>{}(x) % capacity;
        }

        // Resizes the table to a specific capacity and rehashes elements
        void resize(int new_capacity) {
            capacity = new_capacity;
            std::vector<HashNode<T>*> new_table(capacity, nullptr);

            for (size_t i = 0; i < table.size(); i++) {
                HashNode<T>* current = table[i];
                while (current != nullptr) {
                    HashNode<T>* next = current->next;             // save next before moving
                    size_t h = std::hash<T>{}(current->value) % capacity; // new hash
                    
                    // Prepend into the new table's bucket
                    current->next = new_table[h];
                    new_table[h] = current;
                    
                    current = next;
                }
            }
            table = std::move(new_table);
        }

    public:
        // Constructor initializes the hash table with a base capacity
        ChainedHashSet(int initial_capacity = 8) : n(0), capacity(initial_capacity) {
            table.resize(capacity, nullptr);
        }

        // Destructor frees dynamically allocated nodes
        ~ChainedHashSet() {
            for (int i = 0; i < capacity; i++) {
                HashNode<T>* current = table[i];
                while (current != nullptr) {
                    HashNode<T>* next = current->next;
                    delete current;
                    current = next;
                }
            }
        }

        // The Operations
        bool add(T x) override {
            if (contains(x)) {
                return false;                                      // x already in set
            }

            // Expand table if the load factor exceeds 1 (n > capacity)
            if (n + 1 > capacity) {
                resize(capacity * 2);
            }

            size_t h = hash(x);
            HashNode<T>* newNode = new HashNode<T>(x);
            
            // Insert at the head of the chained list for the target bucket
            newNode->next = table[h];
            table[h] = newNode;
            n++;
            
            return true;
        }

        bool remove(T x) override {
            size_t h = hash(x);
            HashNode<T>* current = table[h];
            HashNode<T>* prev = nullptr;

            while (current != nullptr) {
                if (current->value == x) {
                    // Unlink the node from the chain
                    if (prev == nullptr) {
                        table[h] = current->next;                  // removing the head of the list
                    } else {
                        prev->next = current->next;                // removing from the middle/end
                    }
                    
                    delete current;                                // free memory
                    n--;
                    
                    // Shrink the table if it gets too empty (maintaining a minimum capacity of 8)
                    if (capacity > 8 && 3 * n < capacity) {
                        resize(capacity / 2);
                    }
                    
                    return true;
                }
                prev = current;
                current = current->next;
            }
            return false;                                          // x not found
        }

        bool contains(T x) const override {
            size_t h = hash(x);
            HashNode<T>* current = table[h];

            // Traverse the linked list at bucket `h`
            while (current != nullptr) {
                if (current->value == x) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        int size() const override {
            return n;
        }
};