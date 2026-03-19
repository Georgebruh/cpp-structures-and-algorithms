#pragma once
#include "../Interfaces/sset.hpp"
#include "../Base_Structures/skiplist_node.hpp"
#include <cstdlib>

template <typename T>
class Skiplist : public SSet<T> {
    private:
        static const int MAX_LEVEL = 32;           // maximum number of levels
        SkiplistNode<T>* head;                     // sentinel head node
        int n;                                     // number of elements in the set
        int h;                                     // current maximum height in use

        int pickHeight() {
            int height = 1;
            while(height < MAX_LEVEL && (rand() % 2 == 0)) {
                height++;
            }
            return height;
        }

        void findPredecessors(T x, SkiplistNode<T>* update[]) const {
            SkiplistNode<T>* current = head;

            for(int i = h - 1; i >= 0; i--) {                                               // start from the highest level
                while(current->next[i] != nullptr &&                                        // while not at end
                    current->next[i]->value < x) {                                          // and next value is less than x
                    current = current->next[i];                                             // move forward           
                }       
                update[i] = current;                                                        // record last node at this level
            }
        }

    public:
        Skiplist() : n(0), h(1) {
            head = new SkiplistNode<T>(T(), MAX_LEVEL);                                     // sentinel head with max levels
        }

        ~Skiplist() {
            SkiplistNode<T>* current = head->next[0];                                       // start from first real node
            while (current != nullptr) {
                SkiplistNode<T>* next = current->next[0];                                   // save next before deleting
                delete current;
                current = next;
            }
            delete head;               
        }

        // The Operations
        bool add(T x) override {
            SkiplistNode<T>* update[MAX_LEVEL];                                             // predecessors at each level
            findPredecessors(x, update);
    
            // check if x already exists
            SkiplistNode<T>* found = update[0]->next[0];
            if (found != nullptr && found->value == x) {
                return false;                                                              // x already in set
            }
    
            // create new node with random height
            int newHeight = pickHeight();
            SkiplistNode<T>* newNode = new SkiplistNode<T>(x, newHeight);
    
            // if new node is taller than current height, update head links
            if (newHeight > h) {
                for (int i = h; i < newHeight; i++) {
                    update[i] = head;                                                     // head is predecessor at new levels
                }
                h = newHeight;                                                            // update current max height
            }
    
            // splice new node into each level
            for (int i = 0; i < newHeight; i++) {
                newNode->next[i] = update[i]->next[i];                                   // new node points to successor
                update[i]->next[i] = newNode;                                            // predecessor points to new node
            }
    
            n++;
            return true;
        }

        bool remove(T x) override {
            SkiplistNode<T>* update[MAX_LEVEL];                       // predecessors at each level
            findPredecessors(x, update);
    
            // check if x exists
            SkiplistNode<T>* target = update[0]->next[0];
            if (target == nullptr || target->value != x) {
                return false;                                         // x not in set
            }
    
            // splice target out of each level it participates in
            for (int i = 0; i < h; i++) {
                if (update[i]->next[i] != target) break;             // target doesn't reach this level
                update[i]->next[i] = target->next[i];                // skip over target
            }
    
            delete target;                                            // free the removed node
    
            // lower h if top levels are now empty
            while (h > 1 && head->next[h - 1] == nullptr) {
                h--;
            }
    
            n--;
            return true;
        }
    
        bool contains(T x) const override {
            SkiplistNode<T>* current = head;
    
            for (int i = h - 1; i >= 0; i--) {                      // start from highest level
                while (current->next[i] != nullptr &&               // while not at end
                    current->next[i]->value < x) {                  // and next value is less than x
                    current = current->next[i];                     // move forward
                }
            }
    
            // check if the next node at level 0 is x
            SkiplistNode<T>* found = current->next[0];
            return found != nullptr && found->value == x;
        }

        int size() const override {
            return n;
        }
};
