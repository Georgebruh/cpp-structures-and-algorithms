#include <iostream>
#include <chrono>
#include <string>
#include "arraystack.cpp" 

void benchmarkArrayStack() {
    for (int N = 1000; N <= 1000000; N += 1000) {
        
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

int main(int argc, char* argv[]) {
    // 1. Ensure an argument was provided
    if (argc < 2) {
        std::cerr << "Error: No data structure specified.\n";
        std::cerr << "Usage: .\\benchmark.exe [Stack|Queue|...]\n";
        return 1;
    }

    // 2. Read the argument passed by the Python GUI
    std::string adt_choice = argv[1];

    // 3. Route to the correct benchmark
    if (adt_choice == "ArrayStack") {
        benchmarkArrayStack();
    } 

    // put else here to select other ADTS
    else {
        // If Python sends a name we haven't built yet, throw an error
        std::cerr << "Error: Unknown data structure '" << adt_choice << "'.\n";
        return 1;
    }

    return 0;
}