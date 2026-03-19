#include <iostream>
#include <stdexcept>
#include "../Implementations/dll_list.cpp"

#define ASSERT(condition, message) \
    if (condition) { std::cout << "  [PASS] " << message << std::endl; } \
    else { std::cout << "  [FAIL] " << message << std::endl; }

int main() {
    std::cout << "=== DLList Test Cases ===" << std::endl << std::endl;

    // Test 1: empty list on creation
    std::cout << "-- Test 1: empty list on creation --" << std::endl;
    DLList<int> l1;
    ASSERT(l1.size() == 0, "new list should have size 0");
    std::cout << std::endl;

    // Test 2: add and get
    std::cout << "-- Test 2: add and get --" << std::endl;
    DLList<int> l2;
    l2.add(0, 10);
    l2.add(1, 20);
    l2.add(2, 30);
    ASSERT(l2.get(0) == 10, "index 0 should be 10");
    ASSERT(l2.get(1) == 20, "index 1 should be 20");
    ASSERT(l2.get(2) == 30, "index 2 should be 30");
    ASSERT(l2.size() == 3,  "size should be 3");
    std::cout << std::endl;

    // Test 3: add in the middle
    std::cout << "-- Test 3: add in the middle --" << std::endl;
    DLList<int> l3;
    l3.add(0, 10);
    l3.add(1, 30);
    l3.add(1, 20);  // insert 20 between 10 and 30
    ASSERT(l3.get(0) == 10, "index 0 should be 10");
    ASSERT(l3.get(1) == 20, "index 1 should be 20");
    ASSERT(l3.get(2) == 30, "index 2 should be 30");
    std::cout << std::endl;

    // Test 4: set replaces value and returns old
    std::cout << "-- Test 4: set --" << std::endl;
    DLList<int> l4;
    l4.add(0, 10);
    l4.add(1, 20);
    int old = l4.set(1, 99);
    ASSERT(old       == 20, "set should return old value 20");
    ASSERT(l4.get(1) == 99, "index 1 should now be 99");
    ASSERT(l4.size() == 2,  "size should still be 2");
    std::cout << std::endl;

    // Test 5: remove returns value and shrinks list
    std::cout << "-- Test 5: remove --" << std::endl;
    DLList<int> l5;
    l5.add(0, 10);
    l5.add(1, 20);
    l5.add(2, 30);
    int removed = l5.remove(1);
    ASSERT(removed   == 20, "remove should return 20");
    ASSERT(l5.get(0) == 10, "index 0 should still be 10");
    ASSERT(l5.get(1) == 30, "index 1 should now be 30");
    ASSERT(l5.size() == 2,  "size should be 2");
    std::cout << std::endl;

    // Test 6: remove from front
    std::cout << "-- Test 6: remove from front --" << std::endl;
    DLList<int> l6;
    l6.add(0, 10);
    l6.add(1, 20);
    l6.remove(0);
    ASSERT(l6.get(0) == 20, "index 0 should now be 20 after removing front");
    ASSERT(l6.size() == 1,  "size should be 1");
    std::cout << std::endl;

    // Test 7: remove from back
    std::cout << "-- Test 7: remove from back --" << std::endl;
    DLList<int> l7;
    l7.add(0, 10);
    l7.add(1, 20);
    l7.remove(1);
    ASSERT(l7.get(0) == 10, "index 0 should still be 10");
    ASSERT(l7.size() == 1,  "size should be 1");
    std::cout << std::endl;

    // Test 8: out of range exceptions
    std::cout << "-- Test 8: out of range exceptions --" << std::endl;
    DLList<int> l8;
    l8.add(0, 10);

    bool caughtGet = false;
    try { l8.get(5); } catch (const std::out_of_range&) { caughtGet = true; }
    ASSERT(caughtGet, "get out of range should throw");

    bool caughtSet = false;
    try { l8.set(5, 99); } catch (const std::out_of_range&) { caughtSet = true; }
    ASSERT(caughtSet, "set out of range should throw");

    bool caughtRemove = false;
    try { l8.remove(5); } catch (const std::out_of_range&) { caughtRemove = true; }
    ASSERT(caughtRemove, "remove out of range should throw");
    std::cout << std::endl;

    // Test 9: works with string type
    std::cout << "-- Test 9: works with string type --" << std::endl;
    DLList<std::string> l9;
    l9.add(0, "hello");
    l9.add(1, "world");
    ASSERT(l9.get(0) == "hello", "index 0 should be hello");
    ASSERT(l9.get(1) == "world", "index 1 should be world");
    l9.set(0, "hi");
    ASSERT(l9.get(0) == "hi",    "index 0 should now be hi");
    std::cout << std::endl;

    std::cout << "=== All tests completed! ===" << std::endl;
    return 0;
}