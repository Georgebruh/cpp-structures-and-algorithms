<div align="center">

# 🧱 DSA in C++: Abstract to Concrete
*A comprehensive library mapping Abstract Data Types to concrete, high-performance C++ Data Structures, featuring live Python-based benchmarking.*

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Matplotlib](https://img.shields.io/badge/Matplotlib-11557c?style=for-the-badge&logo=python&logoColor=white)
![GCC Compiler](https://img.shields.io/badge/GCC_MinGW-A3E544?style=for-the-badge&logo=gnu&logoColor=black)
![VS Code](https://img.shields.io/badge/VS_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)

<br>
</div>

---
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

| Abstract Data Type (Docs) | Core Contract | C++ Interface | C++ Implementation | Demo App | Real-World Application |
|:---|:---|:---|:---|:---|:---|
| **[Stack](./ArrayStack.md)** | Last-In-First-Out (LIFO) | [`list.hpp`](./Interfaces/list.hpp) | [`ArrayStack`](./Implementations/arraystack.cpp) | [`ArrayStackapp`](./Applications/ArrayStackapp.cpp) | Browser history back button |
| **Queue** | First-In-First-Out (FIFO) | [`queue.hpp`](./Interfaces/queue.hpp) | [`SLL Queue`](./Implementations/sll_queue.cpp) | [`sll_app`](./Applications/sll_application.cpp) | Printer document scheduling |
| **[Priority Queue](./PriorityQueue.md)** | Highest priority element is removed first | *N/A* | [`Meldable Heap`](./Implementations/meldable_heap.cpp) | [`pq_app`](./Applications/pq_application.cpp) | ER Triage System (Medical emergencies by severity) |
| **Deque** | Double-ended queue; insert/remove at both ends | [`deque.hpp`](./Interfaces/deque.hpp) | [`Array Deque`](./Implementations/array_deque.cpp) | [`array_deque_app`](./Applications/array_deque_app.cpp) | Palindrome checking |
| **List** | Ordered sequence of elements with positional access | [`list.hpp`](./Interfaces/list.hpp) | [`DLL List`](./Implementations/dll_list.cpp) | [`dll_app`](./Applications/dll_application.cpp) | Music player playlists |
| **Sorted Set** | Collection of unique elements maintained in sorted order | [`sset.hpp`](./Interfaces/sset.hpp) | [`SkipList SSet`](./Implementations/skiplist_sset.cpp) | [`skiplist_app`](./Applications/skiplist_application.cpp) | Game leaderboards |
| **[Unsorted Set](./ChainedHashSet.md)** | Collection of unique elements in no particular order | *N/A* | [`Chained Hash Set`](./Implementations/chained_hash_set.cpp) | [`hash_set_app`](./Applications/hash_set_application.cpp) | Unique user registration system (Username availability) |
| **Graph** | Collection of vertices (nodes) and edges (connections) | *N/A* | Adjacency Matrix / List | *N/A* | Social network connections, GPS map routing |
