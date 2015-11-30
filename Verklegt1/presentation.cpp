#include "presentation.h"
#include "domain.h"
#include "person.h"
#include <iomanip>

void loop(){
    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    string message = ""; // General use message
    vector<Person> people; // The data vector
    int longestName; // Longest name var

    // Add data
    populateVector(people);

    // Get longest name
    longestName = findLongestName(people);

    // Print
    display(people, longestName);

    // ===== MAIN =====

    while(command != "q"){
        cout << ">";

        // Get command
        getline(cin, command);

        // Display the vector
        if(command == "display" || command == "list"){
            display(people, longestName);
        }
        // Sort
        else if(command.substr(0,4) == "sort"){
            sortNames(people, command);
            display(people, longestName);
        }
        // Search
        else if(command.substr(0,6) == "search"){
            vector<Person> results = search(people, command, message);
            if(message == ""){
                display(results, longestName);
            }
            else{
                cout << message << endl;
            }
        }
        // Add
        else if(command == "add") {
            add(people);
        }
        // Write to database
        else if(command == "save") {
            addInfo(people);
        }
        // Help
        else if(command == "help"){
            help(command);
        }
        // Quit
        else if(command == "q"){
            break;
        }
        // Invalid
        else if(command != ""){
            cout << "Invalid command." << endl;
        }
    }
}

// Display
void display(vector<Person> p, int longestName){
    cout << "| ";
    cout << left << setw(longestName) << "Name" << " | ";
    cout << setw(6) << "Gender" << " | ";
    cout << setw(10) << "Birth date" << " | ";
    cout << setw(10) << "Death date" << " | ";
    cout << setw(4) << "Country" << endl;

    for(int i = 0; i < (47 + longestName); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].display(longestName);
    }
}

// Help
void help(string command){
    cout << command << endl;
}
