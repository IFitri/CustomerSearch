#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAX_CUSTOMERS = 1000;
const string FILENAME = "customer_data.txt";

struct cust_data {
    string customer_fullname;
    long long customer_id;
};

cust_data customer[MAX_CUSTOMERS];
int custCount = 0;

/* Generate 1000 unique names
void generateCustomers() {
    const string firstNamesArray[] = {
        "John", "Alice", "Robert", "Emily", "Michael", "Emma",
        "David", "Sophia", "Daniel", "Olivia", "James", "Ava",
        "William", "Isabella", "Joseph", "Mia", "Ethan", "Charlotte",
        "Benjamin", "Amelia", "Alexander", "Harper", "Henry", "Abigail",
        "Matthew", "Ella", "Samuel", "Scarlett", "Jackson", "Grace",
        "Logan", "Lily", "Anthony", "Chloe", "Andrew"
    };

    const string lastNamesArray[] = {
        "Smith", "Johnson", "Williams", "Brown", "Jones", "Miller",
        "Davis", "Garcia", "Rodriguez", "Martinez", "Hernandez", "Lopez",
        "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore",
        "Jackson", "Martin", "Lee", "Perez", "Thompson", "White",
        "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson",
        "Walker", "Young", "Allen", "King", "Wright"
    };

    int firstNameCount = sizeof(firstNamesArray) / sizeof(string);
    int lastNameCount = sizeof(lastNamesArray) / sizeof(string);

    vector<string> firstNames(firstNamesArray, firstNamesArray + firstNameCount);
    vector<string> lastNames(lastNamesArray, lastNamesArray + lastNameCount);

    set<string> nameSet;
    srand(static_cast<unsigned int>(time(NULL)));

    while (custCount < MAX_CUSTOMERS) {
        string fullName = firstNames[rand() % firstNameCount] + " " + lastNames[rand() % lastNameCount];
        if (nameSet.find(fullName) == nameSet.end()) {
            nameSet.insert(fullName);
            customer[custCount].customer_fullname = fullName;
            customer[custCount].customer_id = 1000LL + custCount; // Example base ID
            custCount++;
        }
    }
}
*/

// Save to file
void saveToFile() {
    ofstream outFile(FILENAME.c_str());
    for (int i = 0; i < custCount; ++i) {
        outFile << customer[i].customer_fullname << "\n"
                << customer[i].customer_id << "\n";
    }
    outFile.close();
}

// Load from file
void loadFromFile() {
    ifstream inFile(FILENAME.c_str());
    if (!inFile) return;

    custCount = 0;
    while (getline(inFile, customer[custCount].customer_fullname)) {
        inFile >> customer[custCount].customer_id;
        inFile.ignore(); // ignore newline
        custCount++;
        if (custCount >= MAX_CUSTOMERS) break;
    }

    inFile.close();
}

// Sort by customer_id descending
bool compareByName(const cust_data &a, const cust_data &b) {
    return a.customer_fullname < b.customer_fullname;
}

// Display list
void printList() {
    system("cls"); // or use system("clear"); for Unix/Linux

    if (custCount == 0) {
        cout << "\nNo customer in the list.\n";
        return;
    }

    cout << "\n--- Customer Data ---\n";
    for (int i = 0; i < custCount; ++i) {
        cout << i + 1 << ". " << customer[i].customer_fullname
             << " | Customer ID: " << customer[i].customer_id << "\n";
    }
}

int main() {
    char choice;
    do {
        cout << "\n\n=== MENU OPTIONS ===\n";
//        cout << "G - Generate 1000 random customers\n";
        cout << "R - Display customer data\n";
        cout << "F - Find customer (coming soon)\n";
        cout << "E - Exit program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice) {
/*            case 'G':
                custCount = 0;
                generateCustomers();
                saveToFile();
                cout << "Generated and saved 1000 unique customer records.\n";
                break;
*/

            case 'R':
                loadFromFile();
                sort(customer, customer + custCount, compareByName);
                printList();
                break;
            case 'F':
                cout << "Find feature coming soon.\n";
                break;
            case 'E':
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 'E');

    return 0;
}

