# ArrayDeque Implementation Guide

### 1. Overview of ArrayDeque
The `ArrayDeque` is a concrete data structure that implements a double ended queue using a contiguous block of memory. It treats the physical array as a circular track which allows adding and removing elements from both the very front and the very back with maximum efficiency.

### 2. Architectural Components
The `ArrayDeque` relies on a custom base array for memory management and a strict interface to ensure standardization across different data structures in the repository.

#### A. The Deque Interface ([`deque.hpp`](./Interfaces/deque.hpp))
`ArrayDeque` inherits from a generic template interface class called `Deque<T>`. This interface dictates that any conforming double ended queue must implement specific core methods to interact with the edges of the data.
* **addFirst(T x)** and **addLast(T x)** Inserts elements directly at the front or the back of the queue.
* **removeFirst()** and **removeLast()** Extracts and returns elements from the exact front and back edges.
* **size()** Returns the current number of active elements.

#### B. Raw Memory Management ([`array.cpp`](./Base_Structures/array.cpp))
Instead of relying on standard C++ templates the implementation utilizes a custom dynamic array struct called `array<T>` to manage memory manually.
* **Allocation and Cleanup** The constructor takes an integer and allocates a raw array on the heap. To prevent memory leaks the destructor explicitly frees this memory when the structure is deleted.
* **The Copy Helper** Because raw arrays cannot be resized once created migrating data to a new array is necessary when the deque grows or shrinks. The struct provides a static copy method to efficiently transfer elements from a source array to a destination array.

---

### 3. Deep Dive into ArrayDeque Logic ([`array_deque.cpp`](./Implementations/array_deque.cpp))
The `ArrayDeque` class maintains three critical variables. It tracks a custom array called `a` for the backing memory alongside an integer `n` for the current number of elements and an integer `j` to remember exactly where the front of the line begins. 

#### The Circular Wraparound Mechanism
The true power of this structure comes from how it handles the physical boundaries of the array memory. It utilizes simple division remainders to wrap around the ends seamlessly. If the front of the line is at index zero and a new element is added to the front the index loops backwards to the very last available slot in the physical memory. 

#### The resize() Mechanism
Because arrays are fixed in size the `ArrayDeque` must dynamically manage its capacity while carefully unfolding the circular data.
* When triggered the resize function creates a new array `b` with double the current capacity.
* It copies the `n` existing elements from array `a` to array `b` and forces the front of the line back to index zero to straighten out the data.
* Finally it swaps the internal pointers and safely replaces the old array with the newly expanded or shrunken one.

#### Positional Operations add and remove
While highly optimized for the ends the deque can still handle insertions and deletions anywhere by choosing the shortest path to shift data.
* **add(int i, T x)** First it performs bounds checking and triggers a resize if the array is completely full. To insert the new item it checks if the target index is closer to the front or the back of the line. It then shifts the smaller half of the elements to make an empty slot before inserting the new value and incrementing the total count.
* **remove(int i)** After extracting the target element this method shifts the remaining items from the shortest side to fill the gap left by the removed item. After decrementing the total count it checks for under utilization. If the total capacity is three times larger than the number of active elements it calls the resize function to shrink the array and save memory.

#### Core Deque Operations
The specific queue operations utilize the positional methods to interact with the edges perfectly.
* **addFirst** and **addLast** These methods efficiently drop data right at index zero or index `n`.
* **removeFirst** and **removeLast** These methods grab data from the exact edges without needing to shift large amounts of memory around.

---

### 4. Performance Testing and Benchmarking
To validate the efficiency of the circular wraparound logic the project includes a specialized benchmarking suite.

* **The C++ Benchmark ([`benchmark.cpp`](./Benchmarking/benchmark.cpp))** The `benchmarkArrayDeque` tests how well the structure handles operations on both ends simultaneously. It loops through `N` elements, starting from 1,000 up to 1,000,000 in increments of 10,000. For each loop it records, the exact time it takes to add elements split evenly between the front and the back and then remove them all from both ends.
* **Live Data Visualization ([`live_graph.py`](./Benchmarking/live_graph.py))** The data generated by the C++ executable is piped into a Python script. This script reads the input via `sys.stdin.readline()`, parsing the `N` and time values. Using `matplotlib`, it animates a live graph that visually plots the time complexity and performance curve as the elements scale up to 1 million.