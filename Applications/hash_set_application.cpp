#include <iostream>
#include <string>
#include "../Implementations/chained_hash_set.cpp"

void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "   Unique User Registration System\n";
    std::cout << "      (Powered by Chained Hash Set)      \n";
    std::cout << "=========================================\n";
    std::cout << "1. Register new Username\n";
    std::cout << "2. Check Username availability\n";
    std::cout << "3. Delete/Ban Username\n";
    std::cout << "4. View total registered users (Size)\n";
    std::cout << "5. Exit\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Enter your choice: ";
}

int main() {
    // Instantiate the Chained Hash Set to store string Usernames
    ChainedHashSet<std::string> userDatabase;
    int choice = 0;
    std::string username;

    std::cout << "System Booting... Database Initialized.\n";

    while (choice != 5) {
        displayMenu();
        
        // Basic input validation
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter Username to register: ";
                std::cin >> username;
                // add() returns true if successfully added, false if it's a duplicate
                if (userDatabase.add(username)) {
                    std::cout << "[SUCCESS] Username '" << username << "' has been registered!\n";
                } else {
                    std::cout << "[ERROR] Username '" << username << "' is already taken!\n";
                }
                break;
                
            case 2:
                std::cout << "Enter Username to lookup: ";
                std::cin >> username;
                // contains() returns true if found in O(1) expected time
                if (userDatabase.contains(username)) {
                    std::cout << "[INFO] Username '" << username << "' exists in the database.\n";
                } else {
                    std::cout << "[INFO] Username '" << username << "' is available.\n";
                }
                break;
                
            case 3:
                std::cout << "Enter Username to remove: ";
                std::cin >> username;
                // remove() returns true if found and deleted, false if not found
                if (userDatabase.remove(username)) {
                    std::cout << "[SUCCESS] Username '" << username << "' has been deleted.\n";
                } else {
                    std::cout << "[ERROR] Username '" << username << "' does not exist.\n";
                }
                break;
                
            case 4:
                std::cout << "[INFO] Total active users in database: " << userDatabase.size() << "\n";
                break;
                
            case 5:
                std::cout << "Shutting down system. Goodbye!\n";
                break;
                
            default:
                std::cout << "[ERROR] Invalid choice. Please select a number from 1 to 5.\n";
        }
    }

    return 0;
}