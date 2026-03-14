#pragma once

template <typename T>
class List {
public:
    virtual ~List() = default;
    virtual int size() const = 0;
    virtual T get(int i) const = 0;
    virtual T set(int i, T x) = 0;
    virtual void add(int i, T x) = 0;
    virtual T remove(int i) = 0;
};