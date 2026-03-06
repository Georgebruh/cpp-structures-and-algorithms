## Part 1: What is an Abstract Data Type (ADT)?

![ADT Blueprint vs Implementation](docs/assets/adt_diagram.png)

In computer science, an **Abstract Data Type (ADT)** is a conceptual model that defines how we interact with data, completely separated from *how* that data is actually stored in the computer's memory. 

Think of an ADT as a strictly enforced contract or a blueprint. For example, a **Queue** is an ADT. Its contract dictates a First-In-First-Out (FIFO) rule with two main operations:
1. `enqueue(item)`: Add an item to the back of the line.
2. `dequeue()`: Remove an item from the front of the line.

The ADT does not care *how* you build the Queue. You could implement it using a dynamically resizing array, a chain of linked memory nodes, or even a system of physical buckets. As long as it strictly follows the FIFO rule, it is a valid Queue.

### How ADTs are structured in this repository
To enforce this separation of concerns, this project utilizes **Interface-based design** using Object-Oriented Programming principles:
* **The Interfaces (The Contracts):** Abstract base classes define what operations a structure *must* support (e.g., `add`, `remove`, `search`), without writing any of the underlying logic.
* **The Implementations (The Engines):** Concrete classes inherit from these interfaces and provide the actual, highly-optimized memory management—whether that means traversing pointers in a Linked List, calculating hashes for a Dictionary, or rotating nodes in a Red-Black Tree.
