#include <iostream>
#include <string>
#include "../Implementations/array_deque.cpp"

int main() {
    std::cout << "=== Array Deque Application VIP Queue Manager ===" << std::endl << std::endl;

    ArrayDeque<std::string> boardingQueue;

    std::cout << "1. Regular guests arrive and line up at the back." << std::endl;
    boardingQueue.addLast("Alice (Regular)");
    boardingQueue.addLast("Bob (Regular)");
    boardingQueue.addLast("Charlie (Regular)");
    
    std::cout << "Current Queue Size: " << boardingQueue.size() << std::endl << std::endl;

    std::cout << "2. VIP guests arrive and skip to the very front." << std::endl;
    boardingQueue.addFirst("David (VIP)");
    boardingQueue.addFirst("Emma (VIP)");

    std::cout << "Current Queue Size: " << boardingQueue.size() << std::endl << std::endl;

    std::cout << "3. The gate opens. Boarding guests from the front of the line." << std::endl;
    std::cout << "  Boarding " << boardingQueue.removeFirst() << std::endl;
    std::cout << "  Boarding " << boardingQueue.removeFirst() << std::endl;
    std::cout << "  Boarding " << boardingQueue.removeFirst() << std::endl;

    std::cout << "\nCurrent Queue Size: " << boardingQueue.size() << std::endl << std::endl;

    std::cout << "4. A regular guest gets tired of waiting and leaves from the back." << std::endl;
    std::cout << "  Leaving " << boardingQueue.removeLast() << std::endl;

    std::cout << "\n5. Final boarding call for all remaining guests." << std::endl;
    while (boardingQueue.size() > 0) {
        std::cout << "  Boarding " << boardingQueue.removeFirst() << std::endl;
    }

    std::cout << "\n=== Boarding Complete ===" << std::endl;
    return 0;
}