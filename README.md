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
| **[Stack](./Interfaces/list.hpp)** | Last-In-First-Out (LIFO) | [`ArrayStack`](./Implementations/arraystack.cpp) | [`Browser History`](./Applications/ArrayStackapp.cpp)  |
| **[Queue](./Interfaces/queue.hpp)** | First-In-First-Out (FIFO) | [`Linked List`](./Implementations/sll_queue.cpp) | [`Printing Documents`](./Applications/sll_application.cpp)  |
| Priority Queue |  | Meldable Heap | |
| **[Deque](./Interfaces/deque.hpp)** | | [`Array Deque`](./Implementations/array_deque.cpp) |  |
| **[List](./Interfaces/list.hpp)** |  | [`Array Deque`](./Implementations/arraydeque_list.cpp), [`DL List`](./Implementations/dll_list.cpp)| [`Task Manager (Array Deque)`](./Applications/arraydeque-list_application.cpp), [`Music Player (DL List)`](./Applications/dll_application.cpp) |
| **[Sorted Set](./Interfaces/sset.hpp)** | | Red-Black Tree, [`Skiplist`](./Implementations/skiplist_sset.cpp) | [`Leaderboard (Skiplist)`](./Applications/skiplist_application.cpp)  |
| Unsorted Set |  | Chained Hash Table |  |
| Graph | | Adjacency Matrix |  |
