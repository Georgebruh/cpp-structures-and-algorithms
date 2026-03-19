#include <iostream>
#include <vector>
#include "../Implementations/sll_queue.cpp"

// Simulates a print queue — demonstrates FIFO (First-In, First-Out) order
// The first document added should always be the first one printed

int main() {
    SLLQueue<std::string> printQueue;

    // enqueue documents in this order
    std::cout << "=== Adding documents to queue ===" << std::endl;
    
    std::vector<std::string> documents = {"report.pdf", "homework.docx", "photo.png"};
    
    // To show what's inputted first
    int counter = 1;
    for (const std::string& doc : documents) {
        printQueue.enqueue(doc);
        std::cout << "Added " << counter++ << ": " << doc << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Total in queue: " << printQueue.size() << std::endl;
    std::cout << "Next to print:  " << printQueue.peek() << std::endl;
    
    // FIFO: first in should be first out
    std::cout << std::endl << "=== Printing documents ===" << std::endl;
    int order = 1;
    while (!printQueue.isEmpty()) {
        std::cout << "Printed " << order++ << ": " << printQueue.dequeue() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Queue empty: " << (printQueue.isEmpty() ? "true" : "false") << std::endl;
    std::cout << "No more to print! Printing finished." << std::endl;

    return 0;
}