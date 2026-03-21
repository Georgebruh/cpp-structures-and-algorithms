# Skiplist Implementation Guide

### 1. Overview of Skiplist
The `Skiplist` is a concrete Data Structure that implements a Sorted Set (unique elements stored in sorted order) using a probabilistic multi-level linked list as its underlying physical building material. Unlike a standard linked list that only has one level of forward pointers, a Skiplist builds multiple levels of "express lanes" that allow searches, insertions, and deletions to skip over large portions of the list — achieving O(log n) expected time complexity without the complexity of tree rotations.

### 2. Architectural Components
The `Skiplist` relies on a custom node struct for memory management and a strict interface to ensure standardization across different data structures in the repository.

#### A. The `SSet` Interface ([`sset.hpp`](./Interfaces/sset.hpp))
`Skiplist` inherits from a generic template interface class called `SSet<T>`. This interface dictates that any conforming sorted set structure must implement the following core methods:
* `add(T x)`: Adds x to the set. Returns true if added, false if already exists.
* `remove(T x)`: Removes x from the set. Returns true if removed, false if not found.
* `contains(T x)`: Returns true if x is in the set.
* `size()`: Returns the number of elements in the set.

#### B. Node-Based Memory Management ([`skiplist_node.hpp`](./Base_Structures/skiplist_node.hpp))
Instead of a simple `next` pointer, each `SkiplistNode<T>` holds a **vector of next pointers** — one per level the node participates in.
* **Structure:** Each `SkiplistNode` holds a `value` of type `T` and a `std::vector<SkiplistNode<T>*> next` array of forward pointers.
* **Height:** Each node has a randomly assigned height determined at insertion. A node of height 3 participates in levels 0, 1, and 2.
* **Allocation & Cleanup:** Nodes are created with `new SkiplistNode<T>(x, height)` during `add` and freed with `delete` during `remove`. The destructor walks level 0 to free all nodes.

#### C. Basic Structure
A Skiplist with 3 levels looks like this — higher levels act as express lanes that skip over multiple nodes:

```
Level 2:  head ──────────────────────────────> [30] -> nullptr
Level 1:  head ───────────> [10] ────────────> [30] -> nullptr
Level 0:  head -> [5] ───-> [10] -> [20] ────> [30] -> nullptr
```

```mermaid
flowchart LR
    H2(head L2) -->|L2| C2["[30]"]
    C2 -->|L2| N2(nullptr)

    H1(head L1) -->|L1| B1["[10]"]
    B1 -->|L1| C1["[30]"]
    C1 -->|L1| N1(nullptr)

    H0(head L0) -->|L0| A0["[5]"]
    A0 -->|L0| B0["[10]"]
    B0 -->|L0| X0["[20]"]
    X0 -->|L0| C0["[30]"]
    C0 -->|L0| N0(nullptr)

    style H0 fill:#8B5CF6,color:#fff
    style H1 fill:#8B5CF6,color:#fff
    style H2 fill:#8B5CF6,color:#fff
    style N0 fill:#e2e8f0,color:#64748b
    style N1 fill:#e2e8f0,color:#64748b
    style N2 fill:#e2e8f0,color:#64748b
```

---

### 3. Deep Dive into `Skiplist` Logic ([`skiplist.cpp`](./Implementations/skiplist.cpp))
The `Skiplist` class maintains four critical variables: a `head` sentinel node (with MAX_LEVEL pointers), an integer `n` (number of elements), an integer `h` (current maximum height in use), and a random number generator for `pickHeight()`.

#### The `pickHeight()` Function
Every new node gets a randomly assigned height. Each additional level is added with 50% probability:

```mermaid
flowchart TD
    A[start with height = 1] --> B{flip coin}
    B -- heads 50% --> C[height++]
    C --> D{height less than MAX_LEVEL?}
    D -- yes --> B
    D -- no --> E[return height]
    B -- tails 50% --> E
    style E fill:#8B5CF6,color:#fff
    style C fill:#bbf7d0,color:#14532d
```

This means roughly 50% of nodes have height 1, 25% have height 2, 12.5% have height 3, and so on — creating a natural pyramid structure.

#### The `findPredecessors(x, update[])` Helper
Before any add or remove, the `update[]` array is filled with the last node visited at each level that comes before x. This is the core search routine:

```mermaid
flowchart TD
    A[start at head, highest level h-1] --> B{next node exists AND next value less than x?}
    B -- yes --> C[move forward at current level]
    C --> B
    B -- no --> D[record current node in update at this level]
    D --> E{more levels below?}
    E -- yes --> F[drop down one level]
    F --> B
    E -- no --> G[update array is complete]
    style G fill:#8B5CF6,color:#fff
    style D fill:#bbf7d0,color:#14532d
```

#### The `add(x)` Operation
Adding a new element splices it into every level it participates in:

```mermaid
flowchart TD
    A[call findPredecessors to fill update array] --> B{does x already exist at update-0-next?}
    B -- yes --> C[return false - duplicate]
    B -- no --> D[generate random height via pickHeight]
    D --> E{new height greater than current h?}
    E -- yes --> F[extend update array with head for new levels]
    F --> G[update h to new height]
    E -- no --> G
    G --> H[splice new node into each level using update array]
    H --> I[increment n, return true]
    style C fill:#fca5a5,color:#7f1d1d
    style I fill:#bbf7d0,color:#14532d
```

#### The `remove(x)` Operation
Removing an element splices it out of every level it participates in:

```mermaid
flowchart TD
    A[call findPredecessors to fill update array] --> B{does x exist at update-0-next?}
    B -- no --> C[return false - not found]
    B -- yes --> D[splice target out of each level using update array]
    D --> E[delete the target node]
    E --> F{are top levels now empty?}
    F -- yes --> G[lower h]
    F -- no --> H[decrement n, return true]
    G --> H
    style C fill:#fca5a5,color:#7f1d1d
    style H fill:#bbf7d0,color:#14532d
```

#### The `contains(x)` Operation
Search traverses from the highest level down, using express lanes to skip ahead:

```
Searching for 20:
Level 2: head -> [30]  → 30 > 20, drop down
Level 1: head -> [10]  → 10 < 20, move forward
         [10] -> [30]  → 30 > 20, drop down
Level 0: [10] -> [20]  → found! return true
```

---

### 4. Key Properties of a Sorted Set
The `Skiplist` enforces these Sorted Set guarantees:
* **No duplicates** — `add` returns false if x already exists
* **Sorted order** — elements are always maintained in ascending order internally
* **Expected O(log n)** — all three operations are logarithmic on average due to the probabilistic level structure

---

### 5. Performance Testing and Benchmarking
To validate the efficiency of the `Skiplist`, the project includes a specialized benchmarking suite.

* **The C++ Benchmark ([`benchmark.cpp`](./Benchmarking/benchmark.cpp)):** The `benchmarkSkiplist` function tests the full add + contains + remove cycle. It loops through `N` elements, starting from 1,000 up to 1,000,000 in increments of 10,000. For each `N`, it adds `N` elements, searches for all `N` elements, then removes all `N` elements, recording the total time using `std::chrono::high_resolution_clock` and outputting as `N,duration`.
* **Live Data Visualization ([`live_graph.py`](./Benchmarking/live_graph.py)):** The data is piped into a Python script via `subprocess.Popen`, animating a live graph of the performance curve as N scales up.

---

### 6. Observed Performance Characteristics
The Skiplist's O(log n) per operation means the total benchmark time for N operations is O(n log n):

![Skiplist Benchmark](./Assets/Skiplist_Performance.png)

* **Smooth growth phase:** Unlike the DLList and SLLQueue, the Skiplist's O(log n) per operation means it scales much better — each doubling of N only adds a small constant amount of extra work per operation.
* **Heap fragmentation phase:** Like all node-based structures, individual node allocation eventually causes memory scattering and cache misses at large N.
* **Comparison with other structures:**

| Structure | Per Operation | Total Benchmark | Cache Friendly |
|---|---|---|---|
| ArrayStack | O(1) amortized | O(n) | ✅ Yes |
| SLLQueue | O(1) | O(n) | ❌ No |
| DLList | O(n) | O(n²) | ❌ No |
| Skiplist | O(log n) expected | O(n log n) | ❌ No |