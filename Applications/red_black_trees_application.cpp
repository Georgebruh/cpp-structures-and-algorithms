#include <iostream>
#include <string>
#include "../Implementations/red_black_tree.cpp"

int main() {
    std::cout << "=== Security Access Control ===\n\n";

    RedBlackTree<int> authorizedBadges;

    std::cout << "Registering active employee badges...\n";
    authorizedBadges.add(1050);
    authorizedBadges.add(2044);
    authorizedBadges.add(1011);
    authorizedBadges.add(3099);
    
    std::cout << "System online. Total authorized personnel: " << authorizedBadges.size() << "\n\n";
    std::cout << "Type 0 at any time to shut down the scanner.\n\n";

    int scannedBadge;
    bool systemActive = true;

    while (systemActive) {
        std::cout << "Enter badge number to scan: ";
        std::cin >> scannedBadge;

        if (scannedBadge == 0) {
            std::cout << "Shutting down security checkpoint. Goodbye.\n";
            systemActive = false;
        } else {
            std::cout << "Verifying badge " << scannedBadge << "...\n";
            
            if (authorizedBadges.contains(scannedBadge)) {
                std::cout << ">>> Access Granted. Welcome back.\n\n";
            } else {
                std::cout << ">>> Access Denied. Unrecognized badge.\n\n";
            }
        }
    }

    return 0;
}