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

// Updated resize to take a specific new capacity
        void resize(int new_capacity) {
            capacity = new_capacity;
            std::vector<HashNode<T>*> new_table(capacity, nullptr);

            for (int i = 0; i < table.size(); i++) {
                HashNode<T>* current = table[i];
                while (current != nullptr) {
                    HashNode<T>* next = current->next;             
                    size_t h = std::hash<T>{}(current->value) % capacity; 
                    
                    current->next = new_table[h];
                    new_table[h] = current;
                    
                    current = next;
                }
            }
            table = std::move(new_table);
        }

        // Updated add to use the parameterized resize
        bool add(T x) override {
            if (contains(x)) return false;                                      

            if (n + 1 > capacity) {
                resize(capacity * 2); // Double size when full
            }
            // ... (rest of add logic) ...
        }

        // Updated remove to shrink when too sparse
        bool remove(T x) override {
            // ... (find and delete node logic remains the same) ...
                    delete current;                                
                    n--;
                    
                    // NEW: Shrink the table if it gets too empty (but keep a minimum capacity)
                    if (capacity > 8 && 3 * n < capacity) {
                        resize(capacity / 2);
                    }
                    
                    return true;
            // ...
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