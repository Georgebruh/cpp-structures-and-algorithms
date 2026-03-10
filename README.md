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
| **[Stack](./Interfaces/list.hpp)** | Last-In-First-Out (LIFO) | [`ArrayStack`](./Implementations/arraystack.cpp) |  |
| Queue |  | Linked List |  |
| Priority Queue |  | Meldable Heap | |
| Deque | | Array Deque |  |
| List |  | DLL List | |
| Sorted Set | | Red-Black Tree |  |
| Unsorted Set |  | Chained Hash Table |  |
| Graph | | Adjacency Matrix |  |
