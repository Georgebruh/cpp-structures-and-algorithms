#pragma once

template <typename T>
class SortedSet {
    public:
        virtual ~SortedSet() {}

        virtual bool add(T x) = 0;            // Adds an element to the set if it does not already exist
        virtual bool remove(T x) = 0;         // Removes an element from the set
        virtual bool contains(T x) const = 0; // Checks if an element exists within the set
        virtual int size() const = 0;         // Returns the number of elements currently in the set
};