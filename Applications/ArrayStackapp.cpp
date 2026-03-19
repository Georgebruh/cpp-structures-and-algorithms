#include <iostream>
#include <string>
#include "../Implementations/arraystack.cpp"

void displayMenu() {
    std::cout << "\n--- Browser History Menu ---\n";
    std::cout << "1. Visit a new webpage (Push)\n";
    std::cout << "2. Go back (Pop)\n";
    std::cout << "3. View current history (Display Stack)\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option (1-4): ";
}

int main() {
    ArrayStack<std::string> browserHistory;

    std::cout << "Initializing browser and preloading history...\n";
    //we add this pre laoded inputs
    browserHistory.push("https://www.google.com");
    browserHistory.push("https://www.github.com");
    browserHistory.push("https://www.stackoverflow.com");
    
    std::cout << "Preloaded 3 pages.\n";
    int choice = 0;
    std::string newPage;

    while (choice != 4) {

        if (browserHistory.size() > 0) {
            // Since there is no peek() method, we use get(size - 1) to look at the top item
            std::cout << "\n[CURRENT PAGE]: " << browserHistory.get(browserHistory.size() - 1) << "\n";
        } else {
            std::cout << "\n[CURRENT PAGE]: (Empty / Blank Page)\n";
        }

        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the URL of the new page: ";
                std::cin >> newPage;
                browserHistory.push(newPage);
                std::cout << "Navigated to " << newPage << "!\n";
                break;

            case 2:
                try {
                    // Try to pop the top element
                    std::string poppedPage = browserHistory.pop();
                    std::cout << "Going back... Left " << poppedPage << "\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: No history to go back to! (Stack is empty)\n";
                }
                break;

            case 3:
                std::cout << "\n--- Full Browser History (Bottom to Top) ---\n";
                if (browserHistory.size() == 0) {
                    std::cout << "History is empty.\n";
                } else {
                    // We can use the get() method from your List interface to iterate
                    for (int i = 0; i < browserHistory.size(); i++) {
                        std::cout << i + 1 << ": " << browserHistory.get(i);
                        if (i == browserHistory.size() - 1) {
                            std::cout << " <- (Current)";
                        }
                        std::cout << "\n";
                    }
                }
                break;

            case 4:
                std::cout << "Closing browser. Goodbye!\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                // Clear input buffer in case of invalid characters
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
        }
    }

    return 0;
}