#include <iostream>
#include <string>
#include <stdexcept>
#include "../Implementations/dll_list.cpp"

void displayMenu() {
    std::cout << "===== Playlist Menu =====" << std::endl;
    std::cout << "1. Add a song" << std::endl;           // add
    std::cout << "2. Remove a song" << std::endl;        // remove
    std::cout << "3. View a song" << std::endl;          // get
    std::cout << "4. Rename a song" << std::endl;        // set
    std::cout << "5. View all songs" << std::endl;       
    std::cout << "6. Exit"  << std::endl;
    std::cout << "Choose an option (1-6)" << std::endl;
}

int main() {
    DLList<std::string> playlist;

    std::cout << " ===== Music Player ====" << std::endl;
    std::cout << "Loading recently played songs..." << std::endl;

    playlist.add(0, "Hawak Mo Ang Beat Remix - DJ Mogo");
    playlist.add(1, "Tanging Ina - Ai-Ai delas Alas");
    playlist.add(2, "Ale - The Bloomfields");

    std::cout << "Loaded " << playlist.size() << " recently played songs" << std::endl;

    std::cout << "Recently played songs: " << std::endl;
    for(int i = 0; i < playlist.size(); i++) {
        std::cout << i << ": " << playlist.get(i) << std::endl;
    }

    int choice = 0;
    std::string song;
    int index;

    while(choice != 6) {
        std::cout << "Total Songs: " << playlist.size() << std::endl;

        if(playlist.size() > 0) {
            std::cout << " | Now Playing: " << playlist.get(0);
        }

        std::cout << "\n";

        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // add
                std::cout << "Enter position (0 to " << playlist.size() << "): ";
                std::cin >> index;
                std::cout << "Enter song name: ";
                std::cin.ignore();
                std::getline(std::cin, song);
                try {
                    playlist.add(index, song);
                    std::cout << "Added \"" << song << "\" at position " << index << "." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 2: // remove
                std::cout << "Enter position to remove (0 to " << playlist.size() - 1 << "): ";
                std::cin >> index;
                try {
                    std::string r = playlist.remove(index);
                    std::cout << "Removed \"" << r << "\" from position " << index <<  "." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 3: // get
                std::cout << "Enter position to view (0 to " << playlist.size() - 1 << "): ";
                std::cin >> index;
                try {
                    std::cout << "Song at " << index << ":" << playlist.get(index) << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 4: // set
                std::cout << "Enter position to replace (0 to " << playlist.size() - 1 << "): ";
                std::cin >> index;
                std::cout << "Enter new song name: ";
                std::cin.ignore();
                std::getline(std::cin, song);
                try {
                    std::string n = playlist.set(index, song);
                    std::cout << "Replaced \"" << n << "\" with \"" << song << "\"." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;

            case 5:
                std::cout << "\n--- Full Playlist ---\n";
                if (playlist.size() == 0) {
                    std::cout << "Playlist is empty.\n";
                } else {
                    for (int i = 0; i < playlist.size(); i++) {
                        std::cout << i << ": " << playlist.get(i);
                        if (i == 0) std::cout << " <- (Now Playing)";
                        std::cout << "\n";
                    }
                }
                break;
            
            case 6:
                std::cout << "Exiting playlist manager. Goodbye!\n";
                break;
 
            default:
                std::cout << "Invalid choice. Please try again.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
        }

    }

    return 0;
}
