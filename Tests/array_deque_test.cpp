#include <iostream>
#include <stdexcept>
#include <string>
#include "../Implementations/array_deque.cpp"

#define ASSERT(condition, message) \
    if (condition) { std::cout << "  [PASS] " << message << std::endl; } \
    else { std::cout << "  [FAIL] " << message << std::endl; }

int main() {
    std::cout << "=== ArrayDeque Test Cases ===" << std::endl << std::endl;

    // Test: 1 empty deque on creation
    std::cout << "-- Test: 1 empty deque on creation --" << std::endl;
    ArrayDeque<int> d1;
    ASSERT(d1.size() == 0, "new deque should have size 0");
    std::cout << std::endl;

    // Test: 2 addLast and removeFirst
    std::cout << "-- Test: 2 addLast and removeFirst --" << std::endl;
    ArrayDeque<int> d2;
    d2.addLast(10);
    d2.addLast(20);
    d2.addLast(30);
    ASSERT(d2.size() == 3, "size should be 3");
    ASSERT(d2.removeFirst() == 10, "first removed should be 10");
    ASSERT(d2.removeFirst() == 20, "second removed should be 20");
    ASSERT(d2.size() == 1, "size should now be 1");
    std::cout << std::endl;

    // Test: 3 addFirst and removeFirst
    std::cout << "-- Test: 3 addFirst and removeFirst --" << std::endl;
    ArrayDeque<int> d3;
    d3.addFirst(10);
    d3.addFirst(20);
    d3.addFirst(30);
    ASSERT(d3.removeFirst() == 30, "first removed should be 30");
    ASSERT(d3.removeFirst() == 20, "second removed should be 20");
    std::cout << std::endl;

    // Test: 4 mixed operations and wraparound
    std::cout << "-- Test: 4 mixed operations and wraparound --" << std::endl;
    ArrayDeque<int> d4;
    d4.addLast(1);
    d4.addLast(2);
    d4.addFirst(0);
    d4.addLast(3);
    ASSERT(d4.removeFirst() == 0, "front should be 0");
    ASSERT(d4.removeLast() == 3, "back should be 3");
    ASSERT(d4.size() == 2, "size should be 2");
    std::cout << std::endl;

    // Test: 5 dynamic resizing
    std::cout << "-- Test: 5 dynamic resizing --" << std::endl;
    ArrayDeque<int> d5;
    for (int i = 0; i < 20; i++) {
        d5.addLast(i);
    }
    ASSERT(d5.size() == 20, "size should be 20 after adding beyond capacity");
    bool orderCorrect = true;
    for (int i = 0; i < 20; i++) {
        if (d5.removeFirst() != i) orderCorrect = false;
    }
    ASSERT(orderCorrect, "all elements maintained order after resize");
    ASSERT(d5.size() == 0, "size should be 0 after removing all");
    std::cout << std::endl;

    // Test: 6 out of range exceptions
    std::cout << "-- Test: 6 out of range exceptions --" << std::endl;
    ArrayDeque<int> d6;
    bool caughtFirst = false;
    try { d6.removeFirst(); } catch (const std::out_of_range&) { caughtFirst = true; }
    ASSERT(caughtFirst, "removeFirst on empty should throw");

    bool caughtLast = false;
    try { d6.removeLast(); } catch (const std::out_of_range&) { caughtLast = true; }
    ASSERT(caughtLast, "removeLast on empty should throw");
    std::cout << std::endl;

    // Test: 7 works with string type
    std::cout << "-- Test: 7 works with string type --" << std::endl;
    ArrayDeque<std::string> d7;
    d7.addLast("hello");
    d7.addFirst("say");
    d7.addLast("world");
    ASSERT(d7.removeFirst() == "say", "first should be say");
    ASSERT(d7.removeLast() == "world", "last should be world");
    ASSERT(d7.removeFirst() == "hello", "middle should be hello");
    std::cout << std::endl;

    std::cout << "=== All tests completed ===" << std::endl;
    return 0;
}