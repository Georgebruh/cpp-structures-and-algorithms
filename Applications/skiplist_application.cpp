#include <iostream>
#include <string>
#include <stdexcept>
#include "../Implementations/skiplist_sset.cpp"

#define ASSERT(condition, message) \
    if (condition) { std::cout << "  [PASS] " << message << std::endl; } \
    else { std::cout << "  [FAIL] " << message << std::endl; }

void displayMenu() {
    std::cout << "\n===== Leaderboard Menu =====" << std::endl;
    std::cout << "1. Add a score" << std::endl;        // add
    std::cout << "2. Remove a score" << std::endl;     // remove
    std::cout << "3. Check if score exists" << std::endl; // contains
    std::cout << "4. View total scores" << std::endl;  // size
    std::cout << "5. Run tests" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Choose an option (1-6): ";
}

int main() {
    Skiplist<int> leaderboard;

    std::cout << "===== Game Leaderboard (Sorted Set) =====" << std::endl;
    std::cout << "Loading leaderboard scores..." << std::endl;

    // preloaded scores — stored in sorted order automatically
    leaderboard.add(1500);
    leaderboard.add(3200);
    leaderboard.add(750);
    leaderboard.add(4800);
    leaderboard.add(2100);

    std::cout << "Loaded " << leaderboard.size() << " scores." << std::endl;

    // hardcoded demo
    std::cout << "\n--- Quick Demo ---" << std::endl;
    std::cout << "Contains score 3200: "
              << (leaderboard.contains(3200) ? "true" : "false") << std::endl;
    std::cout << "Adding duplicate score 3200: "
              << (leaderboard.add(3200) ? "added" : "already exists") << std::endl;
    std::cout << "Removing score 750: "
              << (leaderboard.remove(750) ? "removed" : "not found") << std::endl;
    std::cout << "Total scores after demo: " << leaderboard.size() << std::endl;

    // user input section
    int choice = 0;
    int score;

    while (choice != 6) {
        std::cout << "\n[TOTAL SCORES]: " << leaderboard.size() << std::endl;
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // add
                std::cout << "Enter score to add: ";
                std::cin >> score;
                if (leaderboard.add(score)) {
                    std::cout << "Added score " << score << " to the leaderboard." << std::endl;
                } else {
                    std::cout << "Score " << score << " already exists in the leaderboard." << std::endl;
                }
                break;

            case 2: // remove
                std::cout << "Enter score to remove: ";
                std::cin >> score;
                if (leaderboard.remove(score)) {
                    std::cout << "Removed score " << score << " from the leaderboard." << std::endl;
                } else {
                    std::cout << "Score " << score << " not found in the leaderboard." << std::endl;
                }
                break;

            case 3: // contains
                std::cout << "Enter score to check: ";
                std::cin >> score;
                if (leaderboard.contains(score)) {
                    std::cout << "Score " << score << " is on the leaderboard." << std::endl;
                } else {
                    std::cout << "Score " << score << " is not on the leaderboard." << std::endl;
                }
                break;

            case 4: // size
                std::cout << "Total scores on leaderboard: " << leaderboard.size() << std::endl;
                break;

            case 5: // tests
                std::cout << "\n===== Running Tests =====" << std::endl;
                {
                    Skiplist<int> t;

                    std::cout << "-- Test 1: empty set --" << std::endl;
                    ASSERT(t.size()         == 0,     "new set should have size 0");
                    ASSERT(t.contains(1)    == false, "empty set should not contain 1");

                    std::cout << "-- Test 2: add --" << std::endl;
                    ASSERT(t.add(100)       == true,  "add 100 should return true");
                    ASSERT(t.add(200)       == true,  "add 200 should return true");
                    ASSERT(t.add(100)       == false, "add duplicate 100 should return false");
                    ASSERT(t.size()         == 2,     "size should be 2");

                    std::cout << "-- Test 3: contains --" << std::endl;
                    ASSERT(t.contains(100)  == true,  "should contain 100");
                    ASSERT(t.contains(200)  == true,  "should contain 200");
                    ASSERT(t.contains(999)  == false, "should not contain 999");

                    std::cout << "-- Test 4: remove --" << std::endl;
                    ASSERT(t.remove(100)    == true,  "remove 100 should return true");
                    ASSERT(t.contains(100)  == false, "should not contain 100 after removal");
                    ASSERT(t.remove(999)    == false, "remove non-existent should return false");
                    ASSERT(t.size()         == 1,     "size should be 1");

                    std::cout << "-- Test 5: no duplicates allowed --" << std::endl;
                    Skiplist<int> s;
                    ASSERT(s.add(500)       == true,  "add 500 should return true");
                    ASSERT(s.add(500)       == false, "add duplicate 500 should return false");
                    ASSERT(s.size()         == 1,     "size should still be 1");

                    std::cout << "-- Test 6: remove then re-add --" << std::endl;
                    ASSERT(s.remove(500)    == true,  "remove 500 should return true");
                    ASSERT(s.add(500)       == true,  "re-add 500 should return true");
                    ASSERT(s.contains(500)  == true,  "should contain 500 again");
                }
                std::cout << "===== All tests completed! =====" << std::endl;
                break;

            case 6:
                std::cout << "Exiting leaderboard. Goodbye!" << std::endl;
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