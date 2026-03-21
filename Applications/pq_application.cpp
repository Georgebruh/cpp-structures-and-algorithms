#include <iostream>
#include <string>
#include "../Implementations/meldable_heap.cpp" // Updated include

struct Patient {
    std::string name;
    int severity; 

    bool operator<(const Patient& other) const {
        return severity < other.severity; // Adjusted for MeldableHeap logic
    }
};

int main() {
    MeldableHeap<Patient> er_triage; // Updated instantiation

    std::cout << "--- ER Triage System Started ---\n";
    
    er_triage.enqueue({"John (Sprained Ankle)", 3});
    er_triage.enqueue({"Alice (Heart Attack)", 10});
    er_triage.enqueue({"Bob (Mild Fever)", 2});
    er_triage.enqueue({"Eve (Broken Arm)", 6});

    std::cout << "Patients registered. Treating by severity:\n\n";

    while (!er_triage.isEmpty()) {
        Patient p = er_triage.dequeue();
        std::cout << "Treating: " << p.name << " [Severity: " << p.severity << "]\n";
    }

    return 0;
}