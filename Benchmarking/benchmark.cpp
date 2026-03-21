#include <iostream>
#include <chrono>
#include <string>
#include "../Implementations/arraystack.cpp"
#include "../Implementations/sll_queue.cpp"
#include "../Implementations/dll_list.cpp"
#include "../Implementations/skiplist_sset.cpp"
#include "../Implementations/array_deque.cpp"
#include "../Implementations/meldable_heap.cpp"
#include "../Implementations/skiplist_sset.cpp"
#include "../Implementations/chained_hash_set.cpp"

void benchmarkArrayStack() {
    for (int N = 1000; N <= 1000000; N += 10000) {
        
        ArrayStack<int> stack; 
        
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < N; ++i) {
            stack.push(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
}

void benchmarkSLLQueue() {
    for (int N = 1000; N <= 1000000; N += 1000) {

        SLLQueue<int> queue;

        auto start = std::chrono::high_resolution_clock::now();

        // enqueue N elements
        for (int i = 0; i < N; ++i) {
            queue.enqueue(i);
        }

        // dequeue all N elements
        while (!queue.isEmpty()) {
            queue.dequeue();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
}

void benchmarkDLList() {
    for (int N = 1000; N <= 1000000; N += 1000) {

        DLList<int> list;

        auto start = std::chrono::high_resolution_clock::now();

        // add N elements to the back
        for (int i = 0; i < N; ++i) {
            list.add(i, i);
        }

        // remove all N elements from the front
        for (int i = 0; i < N; ++i) {
            list.remove(0);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }    
}

void benchmarkSkiplist() {
    for (int N = 1000; N <= 1000000; N += 1000) {
        Skiplist<int> skiplist;

        auto start = std::chrono::high_resolution_clock::now();

        // add N elements
        for (int i = 0; i < N; ++i) {
            skiplist.add(i);
        }

        // search for all N elements
        for (int i = 0; i < N; ++i) {
            skiplist.contains(i);
        }

        // remove all N elements
        for (int i = 0; i < N; ++i) {
            skiplist.remove(i);
        }
    }
}

void benchmarkArrayDeque() {
    for (int N = 1000; N <= 1000000; N += 10000) {

        ArrayDeque<int> deque;

        auto start = std::chrono::high_resolution_clock::now();

        // add N elements split between the front and the back
        for (int i = 0; i < N / 2; ++i) {
            deque.addLast(i);
            deque.addFirst(i);
        }

        // remove all N elements from both ends
        for (int i = 0; i < N / 2; ++i) {
            deque.removeFirst();
            deque.removeLast();
        }
    }
}
  
void benchmarkMeldableHeap() {
    for (int N = 1000; N <= 1000000; N += 10000) {
        MeldableHeap<int> pq; 
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < N; ++i) {
            pq.enqueue(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
}

void benchmarkSkiplist() {
    for (int N = 1000; N <= 1000000; N += 10000) {
        Skiplist<int> set; 
        
        auto start = std::chrono::high_resolution_clock::now();

        // Add N elements
        for (int i = 0; i < N; ++i) {
            set.add(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
}

void benchmarkChainedHashSet() {
    for (int N = 1000; N <= 1000000; N += 10000) {
        ChainedHashSet<int> set; 
        
        auto start = std::chrono::high_resolution_clock::now();

        // Add N elements
        for (int i = 0; i < N; ++i) {
            set.add(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
}

int main(int argc, char* argv[]) {
    // 1. Ensure an argument was provided
    if (argc < 2) {
        std::cerr << "Error No data structure specified.\n";
        std::cerr << "Usage .\\benchmark.exe [Stack|Queue|...]\n";
        return 1;
    }

    // 2. Read the argument passed by the Python GUI
    std::string adt_choice = argv[1];

    // 3. Route to the correct benchmark
    if (adt_choice == "ArrayStack") {
        benchmarkArrayStack();
    } 
    else if (adt_choice == "SLLQueue") {
        benchmarkSLLQueue();
    }
    else if (adt_choice == "DLList") {
        benchmarkDLList();
    }
    else if (adt_choice == "Skiplist") {
        benchmarkSkiplist();
    }
    
    else if (adt_choice == "ArrayDeque") {
        benchmarkArrayDeque();
    }
        
    else if (adt_choice == "MeldableHeap") {
        benchmarkMeldableHeap();
    }

    else if (adt_choice == "ChainedHashSet") {
        benchmarkChainedHashSet();
    }
    
    else {
    // ...
        // If Python sends a name we haven't built yet, throw an error
        std::cerr << "Error Unknown data structure '" << adt_choice << "'.\n";
        return 1;
    }

    return 0;
}