# ArrayDequeList Implementation Guide

### 1. Overview of ArrayDequeList
The `ArrayDequeList` is a concrete Data Structure that implements a List (index-based access) by **extending** the `ArrayDeque` class — reusing its circular array as the underlying physical building material. Unlike the `DLList` which allocates individual nodes on the heap, the `ArrayDequeList` stores all elements in one contiguous block of memory, making it significantly more cache-friendly and faster in practice.

### 2. Architectural Components
The `ArrayDequeList` builds on top of two existing components and adds the List interface on top.

#### A. The `List` Interface ([`list.hpp`](./Interfaces/list.hpp))
`ArrayDequeList` inherits from `List<T>`, promising index-based access:
* `get(int i)`: Returns the element at index i.
* `set(int i, T x)`: Replaces the element at index i with x, returns the old value.
* `add(int i, T x)`: Inserts x at index i, shifting elements to the right.
* `remove(int i)`: Removes and returns the element at index i.
* `size()`: Returns the number of elements in the list.

#### B. The `ArrayDeque` Base Class ([`array_deque.cpp`](./Implementations/array_deque.cpp))
`ArrayDequeList` also extends `ArrayDeque`, inheriting its circular buffer and reusing its operations:
* `addFirst(x)` / `addLast(x)` — O(1) amortized insertion at either end
* `removeFirst()` / `removeLast()` — O(1) amortized removal from either end
* `resize()` — dynamic growth and shrinking of the backing array
* `frontIndex` — the starting index of the circular buffer
* `count` — number of elements currently stored
* `a` — the backing `array<T>` struct

#### C. The Circular Buffer
The backing array is not a straight array — it wraps around. `frontIndex` marks where the data starts, and elements are accessed using the circular index formula:

```
actual position = (frontIndex + i) % capacity
```

```mermaid
flowchart LR
    subgraph Backing Array
        direction LR
        I0["[_]"]
        I1["[C]"]
        I2["[D]"]
        I3["[E]"]
        I4["[_]"]
        I5["[A]"]
        I6["[B]"]
    end
    F(frontIndex = 5) --> I5
    style F fill:#8B5CF6,color:#fff
    style I5 fill:#bbf7d0,color:#14532d
    style I6 fill:#bbf7d0,color:#14532d
    style I1 fill:#bbf7d0,color:#14532d
    style I2 fill:#bbf7d0,color:#14532d
    style I3 fill:#bbf7d0,color:#14532d
    style I0 fill:#e2e8f0,color:#64748b
    style I4 fill:#e2e8f0,color:#64748b
```

Logical order: A → B → C → D → E (wraps around the array boundary)

#### D. Inheritance Hierarchy
```mermaid
flowchart TD
    A["List&lt;T&gt; (Interface)"] --> C["ArrayDequeList&lt;T&gt;"]
    B["ArrayDeque&lt;T&gt; (Base Class)"] --> C
    style A fill:#8B5CF6,color:#fff
    style B fill:#8B5CF6,color:#fff
    style C fill:#bbf7d0,color:#14532d
```

---

### 3. Deep Dive into `ArrayDequeList` Logic ([`array_deque_list.cpp`](./Implementations/array_deque_list.cpp))
The `ArrayDequeList` inherits all member variables from `ArrayDeque` — `a`, `frontIndex`, and `count` — and adds the four List operations on top.

#### The Circular Index Formula
Every List operation relies on this formula to convert a logical index `i` into an actual position in the backing array:

```mermaid
flowchart LR
    A["logical index i"] --> B["(frontIndex + i) % capacity"]
    B --> C["actual array position"]
    style B fill:#8B5CF6,color:#fff
    style C fill:#bbf7d0,color:#14532d
```

#### `get(i)` and `set(i, x)` — O(1)
Both are pure index math — no traversal needed:

```cpp
// get
return a.a[(frontIndex + i) % a.length];

// set
int idx = (frontIndex + i) % a.length;
T old = a.a[idx];
a.a[idx] = x;
return old;
```

This is the biggest advantage over `DLList` — accessing any element is instant regardless of where it is in the list.

#### `add(i, x)` — O(1 + min(i, n-i))
Instead of shifting the entire array, only the **smaller half** is shifted:

```mermaid
flowchart TD
    A["add(i, x) called"] --> B{"i less than count divided by 2?"}
    B -- yes, i is in left half --> C["call addFirst to make room at front"]
    C --> D["shift elements at 0 to i-1 forward by one"]
    D --> E["place x at index i"]
    B -- no, i is in right half --> F["call addLast to make room at back"]
    F --> G["shift elements at count-1 down to i+1 backward by one"]
    G --> E
    style C fill:#bbf7d0,color:#14532d
    style F fill:#bbf7d0,color:#14532d
    style E fill:#8B5CF6,color:#fff
```

Example — `add(1, X)` with elements `[A, B, C, D]`, i=1 is in the left half so shift left:
```
Before: [ A | B | C | D ]
         0   1   2   3

Step 1: addFirst makes room → [ _ | A | B | C | D ]
Step 2: shift 0..0 forward  → [ A | A | B | C | D ]
Step 3: place X at index 1  → [ A | X | B | C | D ]
```

#### `remove(i)` — O(1 + min(i, n-i))
Mirror of `add` — shifts only the smaller half to close the gap:

```mermaid
flowchart TD
    A["remove(i) called"] --> B["save value at index i"]
    B --> C{"i less than count divided by 2?"}
    C -- yes, i is in left half --> D["shift elements at i down to 1 backward by one"]
    D --> E["call removeFirst to close gap at front"]
    C -- no, i is in right half --> F["shift elements at i up to count-2 forward by one"]
    F --> G["call removeLast to close gap at back"]
    E --> H["return saved value"]
    G --> H
    style D fill:#bbf7d0,color:#14532d
    style F fill:#bbf7d0,color:#14532d
    style H fill:#8B5CF6,color:#fff
```

---

### 4. ArrayDequeList vs DLList
Both implement the same `List` ADT but with very different tradeoffs:

| Operation | ArrayDequeList | DLList |
|---|---|---|
| `get(i)` | O(1) — index math | O(n) — must traverse |
| `set(i, x)` | O(1) — index math | O(n) — must traverse |
| `add(i, x)` | O(min(i, n-i)) — shift half | O(min(i, n-i)) — traverse + relink |
| `remove(i)` | O(min(i, n-i)) — shift half | O(min(i, n-i)) — traverse + relink |
| Memory | One contiguous block | One node per element |
| Cache friendly | ✅ Yes | ❌ No |

```mermaid
flowchart LR
    subgraph DLList - scattered memory
        N1(node) -.-> N2(node) -.-> N3(node) -.-> N4(node)
        style N1 fill:#fca5a5,color:#7f1d1d
        style N2 fill:#fca5a5,color:#7f1d1d
        style N3 fill:#fca5a5,color:#7f1d1d
        style N4 fill:#fca5a5,color:#7f1d1d
    end
    subgraph ArrayDequeList - contiguous memory
        A0["A"] --- A1["B"] --- A2["C"] --- A3["D"]
        style A0 fill:#bbf7d0,color:#14532d
        style A1 fill:#bbf7d0,color:#14532d
        style A2 fill:#bbf7d0,color:#14532d
        style A3 fill:#bbf7d0,color:#14532d
    end
```

---

### 5. Performance Testing and Benchmarking
To validate the efficiency of the `ArrayDequeList`, the project includes a specialized benchmarking suite.

* **The C++ Benchmark ([`benchmark.cpp`](./Benchmarking/benchmark.cpp)):** The `benchmarkArrayDequeList` function tests the full add + get + remove cycle. It loops through `N` elements, starting from 1,000 up to 1,000,000 in increments of 10,000. For each `N`, it adds `N` elements, gets all `N` elements, then removes all `N` from the front, recording total time using `std::chrono::high_resolution_clock` and outputting as `N,duration`.
* **Live Data Visualization ([`live_graph.py`](./Benchmarking/live_graph.py)):** The data is piped into a Python script via `subprocess.Popen`, animating a live graph of the performance curve as N scales up.

---

### 6. Observed Performance Characteristics
The `ArrayDequeList` is expected to outperform `DLList` significantly due to cache locality:

![ArrayDeque List Benchmark](./Assets/ArrayDequeList_Performance.png)


* **Smooth linear growth:** Since all elements are in one contiguous array, the CPU cache can prefetch data efficiently — far fewer cache misses than DLList.
* **Reallocation spikes:** When the backing array doubles in size, all elements must be copied to the new array — causing occasional spikes similar to the ArrayStack.
* **Final comparison of all List implementations:**

| Structure | `get(i)` | Memory | Cache | Spikes from |
|---|---|---|---|---|
| ArrayDequeList | O(1) | Contiguous | ✅ Yes | Resize |
| DLList | O(n) | Scattered | ❌ No | Heap fragmentation |