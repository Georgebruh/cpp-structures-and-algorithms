#include <iostream>
#include <string>
#include <vector>
#include "../Implementations/adjacency_matrix.cpp"

std::string getCityName(int id) {
    if (id == 0) return "Manila";
    if (id == 1) return "Cebu";
    if (id == 2) return "Davao";
    if (id == 3) return "Palawan";
    if (id == 4) return "Bohol";
    return "Unknown";
}

int main() {
    std::cout << "=== Regional Flight Manager ===\n\n";

    AdjacencyMatrix flightMap(5);

    std::cout << "Establishing initial flight routes...\n";
    flightMap.addEdge(0, 1);
    flightMap.addEdge(1, 0);
    flightMap.addEdge(1, 2);
    flightMap.addEdge(0, 3);
    flightMap.addEdge(1, 4);

    std::cout << "System online.\n";

    bool systemActive = true;
    int choice;

    while (systemActive) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1 Check if a direct flight exists\n";
        std::cout << "2 View all outgoing flights from a city\n";
        std::cout << "3 Add a new direct flight route\n";
        std::cout << "0 Shut down system\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Shutting down system. Goodbye.\n";
            systemActive = false;
        } else if (choice == 1) {
            int origin;
            int destination;
            std::cout << "\nCity Codes (0 Manila, 1 Cebu, 2 Davao, 3 Palawan, 4 Bohol)\n";
            std::cout << "Enter origin city code: ";
            std::cin >> origin;
            std::cout << "Enter destination city code: ";
            std::cin >> destination;

            try {
                if (flightMap.hasEdge(origin, destination)) {
                    std::cout << ">>> YES. There is a direct flight from " << getCityName(origin) << " to " << getCityName(destination) << ".\n";
                } else {
                    std::cout << ">>> NO. No direct flight exists for that route.\n";
                }
            } catch (...) {
                std::cout << ">>> Error Invalid city code entered.\n";
            }
        } else if (choice == 2) {
            int origin;
            std::cout << "\nEnter origin city code to view departures: ";
            std::cin >> origin;

            try {
                std::vector<int> departures = flightMap.outEdges(origin);
                std::cout << ">>> Direct flights from " << getCityName(origin) << " go to\n";
                if (departures.empty()) {
                    std::cout << "    No outgoing flights found.\n";
                } else {
                    for (size_t i = 0; i < departures.size(); i++) {
                        std::cout << "    - " << getCityName(departures[i]) << "\n";
                    }
                }
            } catch (...) {
                std::cout << ">>> Error Invalid city code entered.\n";
            }
        } else if (choice == 3) {
            int origin;
            int destination;
            std::cout << "\nEnter origin city code for new route: ";
            std::cin >> origin;
            std::cout << "Enter destination city code: ";
            std::cin >> destination;

            try {
                flightMap.addEdge(origin, destination);
                std::cout << ">>> Success. New direct flight added from " << getCityName(origin) << " to " << getCityName(destination) << ".\n";
            } catch (...) {
                std::cout << ">>> Error Invalid city code entered.\n";
            }
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}