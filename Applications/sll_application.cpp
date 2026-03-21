#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "../Implementations/sll_queue.cpp"

// simple pass/fail helper
#define ASSERT(condition, message) \
    if (condition) { std::cout << "  [PASS] " << message << std::endl; } \
    else { std::cout << "  [FAIL] " << message << std::endl; }

// Tests
void runTests() {
    std::cout << "=== SLLQueue Test Cases ===" << std::endl << std::endl;

    // Test 1: isEmpty on a new queue
    std::cout << "-- Test 1: isEmpty on new queue --" << std::endl;
    SLLQueue<int> q1;
    ASSERT(q1.isEmpty() == true,  "new queue should be empty");
    ASSERT(q1.size() == 0,     "new queue size should be 0");
    std::cout << std::endl;

    // Test 2: enqueue increases size
    std::cout << "-- Test 2: enqueue increases size --" << std::endl;
    SLLQueue<int> q2;
    q2.enqueue(10);
    ASSERT(q2.size() == 1, "size should be 1 after one enqueue");
    ASSERT(q2.isEmpty() == false, "queue should not be empty after enqueue");
    q2.enqueue(20);
    q2.enqueue(30);
    ASSERT(q2.size() == 3, "size should be 3 after three enqueues");
    std::cout << std::endl;

    // Test 3: peek returns front without removing
    std::cout << "-- Test 3: peek returns front without removing --" << std::endl;
    SLLQueue<int> q3;
    q3.enqueue(10);
    q3.enqueue(20);
    ASSERT(q3.peek() == 10,    "peek should return 10 (front)");
    ASSERT(q3.size() == 2,     "size should still be 2 after peek");
    std::cout << std::endl;

    // Test 4: dequeue returns elements in FIFO order
    std::cout << "-- Test 4: dequeue returns elements in FIFO order --" << std::endl;
    SLLQueue<int> q4;
    q4.enqueue(10);
    q4.enqueue(20);
    q4.enqueue(30);
    ASSERT(q4.dequeue() == 10,    "first dequeue should return 10");
    ASSERT(q4.dequeue() == 20,    "second dequeue should return 20");
    ASSERT(q4.dequeue() == 30,    "third dequeue should return 30");
    ASSERT(q4.isEmpty() == true,  "queue should be empty after draining");
    std::cout << std::endl;

    // Test 5: dequeue decreases size
    std::cout << "-- Test 5: dequeue decreases size --" << std::endl;
    SLLQueue<int> q5;
    q5.enqueue(10);
    q5.enqueue(20);
    q5.dequeue();
    ASSERT(q5.size() == 1,     "size should be 1 after one dequeue");
    q5.dequeue();
    ASSERT(q5.size() == 0,     "size should be 0 after draining");
    std::cout << std::endl;

    // Test 6: enqueue after dequeue still works correctly
    std::cout << "-- Test 6: enqueue after partial dequeue --" << std::endl;
    SLLQueue<int> q6;
    q6.enqueue(10);
    q6.enqueue(20);
    q6.dequeue();         // removes 10
    q6.enqueue(30);
    ASSERT(q6.peek() == 20,    "front should now be 20");
    ASSERT(q6.size() == 2,     "size should be 2");
    std::cout << std::endl;

    // Test 7: dequeue on empty queue throws exception
    std::cout << "-- Test 7: dequeue on empty queue throws exception --" << std::endl;
    SLLQueue<int> q7;
    bool caughtDequeue = false;
    try {
        q7.dequeue();
    } catch (const std::underflow_error&) {
        caughtDequeue = true;
    }
    ASSERT(caughtDequeue == true, "dequeue on empty queue should throw underflow_error");
    std::cout << std::endl;

    // Test 8: peek on empty queue throws exception
    std::cout << "-- Test 8: peek on empty queue throws exception --" << std::endl;
    SLLQueue<int> q8;
    bool caughtPeek = false;
    try {
        q8.peek();
    } catch (const std::underflow_error&) {
        caughtPeek = true;
    }
    ASSERT(caughtPeek == true,    "peek on empty queue should throw underflow_error");
    std::cout << std::endl;

    // Test 9: works with string type
    std::cout << "-- Test 9: works with string type --" << std::endl;
    SLLQueue<std::string> q9;
    q9.enqueue("hello");
    q9.enqueue("world");
    ASSERT(q9.peek() == "hello", "peek should return hello");
    ASSERT(q9.dequeue() == "hello", "dequeue should return hello");
    ASSERT(q9.dequeue() == "world", "dequeue should return world");
    ASSERT(q9.isEmpty() == true, "queue should be empty after draining");
    std::cout << std::endl;

    std::cout << "=== All tests completed! ===" << std::endl;
}

// Application
void runApp() {
    SLLQueue<std::string> printQueue;

    // enqueue documents in this order
    std::cout << "=== Adding documents to queue ===" << std::endl;

    std::vector<std::string> documents = {"report.pdf", "homework.docx", "photo.png"};

    // to show what's inputted first
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
}

// Main
int main() {
    runApp();
    std::cout << std::endl << "========================================" << std::endl << std::endl;
    runTests();
    return 0;
}