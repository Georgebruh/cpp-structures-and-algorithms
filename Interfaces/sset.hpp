#pragma once

template <typename T>
class SSet {
    public:
        virtual ~SSet() {}

        virtual bool add(T x) = 0;                      // Adds x to the set. Returns true if added, false if already exists. 
        virtual bool remove(T x) = 0;                   // Removes x from the set. Returns true if removed, false if not found.
        virtual bool contains(T x) const = 0;           // Returns true if x is in the set.
        virtual int size() const = 0;                   // Returns the number of elements in the set. 
};  