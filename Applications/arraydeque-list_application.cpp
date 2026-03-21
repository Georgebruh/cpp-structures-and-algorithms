#include <iostream>
#include <string>
#include <stdexcept>
#include "../Implementations/arraydeque_list.cpp"

#define ASSERT(condition, message) \
    if (condition) { std::cout << "  [PASS] " << message << std::endl; } \
    else { std::cout << "  [FAIL] " << message << std::endl; }

void displayMenu() {
    std::cout << "\n===== Task Manager Menu =====" << std::endl;
    std::cout << "1. Add a task at position" << std::endl;    // add
    std::cout << "2. Remove a task" << std::endl;             // remove
    std::cout << "3. View a task" << std::endl;               // get
    std::cout << "4. Rename a task" << std::endl;             // set
    std::cout << "5. View all tasks" << std::endl;
    std::cout << "6. Run tests" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Choose an option (1-7): ";
}

// Tests
void runTests() {
    std::cout << "\n===== Running Tests =====" << std::endl;
    {
        ArrayDequeList<int> l;

        std::cout << "-- Test 1: empty list --" << std::endl;
        ASSERT(l.size()     == 0,     "new list should have size 0");

        std::cout << "-- Test 2: add and get --" << std::endl;
        l.add(0, 10);
        l.add(1, 20);
        l.add(2, 30);
        ASSERT(l.get(0)     == 10,    "index 0 should be 10");
        ASSERT(l.get(1)     == 20,    "index 1 should be 20");
        ASSERT(l.get(2)     == 30,    "index 2 should be 30");
        ASSERT(l.size()     == 3,     "size should be 3");

        std::cout << "-- Test 3: add in the middle --" << std::endl;
        l.add(1, 15);
        ASSERT(l.get(0)     == 10,    "index 0 should be 10");
        ASSERT(l.get(1)     == 15,    "index 1 should be 15");
        ASSERT(l.get(2)     == 20,    "index 2 should be 20");
        ASSERT(l.size()     == 4,     "size should be 4");

        std::cout << "-- Test 4: set --" << std::endl;
        int old = l.set(1, 99);
        ASSERT(old          == 15,    "set should return old value 15");
        ASSERT(l.get(1)     == 99,    "index 1 should now be 99");

        std::cout << "-- Test 5: remove --" << std::endl;
        int removed = l.remove(1);
        ASSERT(removed      == 99,    "remove should return 99");
        ASSERT(l.get(1)     == 20,    "index 1 should now be 20");
        ASSERT(l.size()     == 3,     "size should be 3");

        std::cout << "-- Test 6: out of range exceptions --" << std::endl;
        bool caughtGet = false;
        try { l.get(99); } catch (const std::out_of_range&) { caughtGet = true; }
        ASSERT(caughtGet,             "get out of range should throw");

        bool caughtSet = false;
        try { l.set(99, 0); } catch (const std::out_of_range&) { caughtSet = true; }
        ASSERT(caughtSet,             "set out of range should throw");

        bool caughtRemove = false;
        try { l.remove(99); } catch (const std::out_of_range&) { caughtRemove = true; }
        ASSERT(caughtRemove,          "remove out of range should throw");
    }
    std::cout << "===== All tests completed! =====" << std::endl;
}

// -----------------------------------------------------------------------
// Application
// -----------------------------------------------------------------------
int main() {
    ArrayDequeList<std::string> taskList;

    std::cout << "===== Task Manager =====" << std::endl;
    std::cout << "Loading tasks..." << std::endl;

    // preloaded tasks
    taskList.add(0, "Buy groceries");
    taskList.add(1, "Do laundry");
    taskList.add(2, "Study for exam");
    taskList.add(3, "Call dentist");

    std::cout << "Loaded " << taskList.size() << " tasks." << std::endl;

    // hardcoded demo
    std::cout << "\n--- Quick Demo ---" << std::endl;
    std::cout << "Task at index 1: " << taskList.get(1) << std::endl;
    std::string old = taskList.set(1, "Do dishes");
    std::cout << "Replaced \"" << old << "\" with \"Do dishes\"" << std::endl;
    std::string removed = taskList.remove(3);
    std::cout << "Removed \"" << removed << "\"" << std::endl;
    std::cout << "Tasks after demo: " << taskList.size() << std::endl;

    // user input section
    int choice = 0;
    std::string task;
    int index;

    while (choice != 7) {
        std::cout << "\n[TOTAL TASKS]: " << taskList.size() << std::endl;
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // add
                std::cout << "Enter position (0 to " << taskList.size() << "): ";
                std::cin >> index;
                std::cout << "Enter task: ";
                std::cin.ignore();
                std::getline(std::cin, task);
                try {
                    taskList.add(index, task);
                    std::cout << "Added \"" << task << "\" at position " << index << "." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 2: // remove
                std::cout << "Enter position to remove (0 to " << taskList.size() - 1 << "): ";
                std::cin >> index;
                try {
                    std::string r = taskList.remove(index);
                    std::cout << "Removed \"" << r << "\"." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 3: // get
                std::cout << "Enter position to view (0 to " << taskList.size() - 1 << "): ";
                std::cin >> index;
                try {
                    std::cout << "Task at " << index << ": " << taskList.get(index) << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 4: // set
                std::cout << "Enter position to rename (0 to " << taskList.size() - 1 << "): ";
                std::cin >> index;
                std::cout << "Enter new task name: ";
                std::cin.ignore();
                std::getline(std::cin, task);
                try {
                    std::string o = taskList.set(index, task);
                    std::cout << "Replaced \"" << o << "\" with \"" << task << "\"." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 5: // display
                std::cout << "\n--- Task List ---" << std::endl;
                if (taskList.size() == 0) {
                    std::cout << "No tasks." << std::endl;
                } else {
                    for (int i = 0; i < taskList.size(); i++) {
                        std::cout << i << ": " << taskList.get(i) << std::endl;
                    }
                }
                break;

            case 6: // tests
                runTests();
                break;

            case 7:
                std::cout << "Exiting task manager. Goodbye!" << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
        }
    }

    return 0;
}