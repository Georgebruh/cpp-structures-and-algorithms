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

| Abstract Data Type | Core Contract | C++ Implementation | Demo App | Real-World Application |
|:---|:---|:---|:---|:---|
| **[Stack](./Interfaces/list.hpp)** | Last-In-First-Out (LIFO) | [`ArrayStack`](./Implementations/arraystack.cpp) | [`ArrayStackapp`](./Applications/ArrayStackapp.cpp) | Browser history back button |
| **[Queue](./Interfaces/queue.hpp)** | First-In-First-Out (FIFO) | [`SLL Queue`](./Implementations/sll_queue.cpp) | [`sll_app`](./Applications/sll_application.cpp) | Printer document scheduling |
| **Priority Queue** | Highest priority element is removed first | [`Meldable Heap`](./Implementations/meldable_heap.cpp) | [`pq_app`](./Applications/pq_application.cpp) | ER Triage System (Medical emergencies by severity) |
| **[Deque](./Interfaces/deque.hpp)** | Double-ended queue; insert/remove at both ends | [`Array Deque`](./Implementations/array_deque.cpp) | [`array_deque_app`](./Applications/array_deque_app.cpp) | VIP Queue Manager|
| **[List](./Interfaces/list.hpp)** | Ordered sequence of elements with positional access | [`DLL List`](./Implementations/dll_list.cpp) | [`dll_app`](./Applications/dll_application.cpp) | Music player playlists |
| **[Sorted Set](./Interfaces/sset.hpp)** | Collection of unique elements maintained in sorted order | [`SkipList SSet`](./Implementations/skiplist_sset.cpp) | [`skiplist_app`](./Applications/skiplist_application.cpp) | Game leaderboards |
| **Unsorted Set** | Collection of unique elements in no particular order | [`Chained Hash Set`](./Implementations/chained_hash_set.cpp) | [`hash_set_app`](./Applications/hash_set_application.cpp) | Unique user registration system (Username availability) |
| **Graph** | Collection of vertices (nodes) and edges (connections) | Adjacency Matrix / List | *N/A* | Social network connections, GPS map routing |