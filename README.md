# What is an Abstract Data Type (ADT)?

In computer science, an **Abstract Data Type (ADT)** is a conceptual model that defines *what* operations can be performed on data, completely separated from *how* those operations are actually programmed in memory. 

Think of an ADT as a strict **contract** or a **blueprint**:
* **The Contract (ADT):** A **Queue** dictates a First-In-First-Out (FIFO) rule. It promises two main actions: `enqueue` (get in line) and `dequeue` (leave the line). 
* **The Concept:** The ADT does not care *how* you build it. It only cares that the final product strictly follows the FIFO rule.

# What is a Data Structure?

While an ADT is the concept, a **Data Structure** is the concrete, physical way data is organized, stored, and managed inside the computer's actual memory (RAM). 

If the ADT is the blueprint, the Data Structure is the physical building material.
* **Examples:** An **Array** (a contiguous block of memory) or a **Linked List** (scattered nodes connected by memory pointers).

## ADT Dashboard

| Abstract Data Type | Core Contract | C++ Implementation | Real-World Application |
|:---|:---|:---|:---|
| **[Stack](./Interfaces/list.hpp)** | Last-In-First-Out (LIFO) | [`ArrayStack`](./Implementations/arraystack.cpp) | Undo/Redo features, Browser history back button |
| **[Queue](./Interfaces/queue.hpp)** | First-In-First-Out (FIFO) | [`SLL Queue`](./Implementations/sll_queue.cpp) | Printer job scheduling, Web server request management |
| **Priority Queue** | Highest priority element is removed first | [`Meldable Heap`](./Implementations/meldable_heap.cpp) | Operating system task scheduling, Dijkstra's algorithm |
| **[Deque](./Interfaces/deque.hpp)** | Double-ended queue; insert/remove at both ends | [`Array Deque`](./Implementations/array_deque.cpp) | Palindrome checking, Stealing jobs in multiprocessor scheduling |
| **[List](./Interfaces/list.hpp)** | Ordered sequence of elements with positional access | [`DLL List`](./Implementations/dll_list.cpp) | Music player playlists, Image carousels |
| **[Sorted Set](./Interfaces/sset.hpp)** | Collection of unique elements maintained in sorted order | [`SkipList SSet`](./Implementations/skiplist_sset.cpp) | Leaderboards, Database indexing for range queries |
| **Unsorted Set** | Collection of unique elements in no particular order | [`Chained Hash Set`](./Implementations/chained_hash_set.cpp) | Spell checker dictionaries, Fast duplicate detection |
| **Graph** | Collection of vertices (nodes) and edges (connections) | Adjacency Matrix / List | Social network connections, GPS map routing |