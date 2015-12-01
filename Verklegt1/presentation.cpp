#include "presentation.h"
#include "domain.h"
#include "person.h"
#include <iomanip>

using namespace std;

void loop(){
    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    string message = ""; // General use message
    vector<Person> people; // The data vector
    int longestName; // Longest name var

    // Add data
    populateVector(people, message);

    if(message == ""){
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
            else if(getCommand(command) == "help"){
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
    else{
        cout << message << endl;
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
void help(string command) {
    (command.length() == 4) ? command = "help" : command = command.erase(0,5);

    if (command == "add") {
        cout << "Follow the instructions on the screen." << endl;
    }
    else if (command == "display") {
        cout << "Prints the database on the screen." << endl;
    }
    else if (command == "search") {
        cout << "Search [string] searches through all the column" << endl;
        cout << "Search -a [string] returns search in ascending order" << endl;
        cout << "Search -b [string] searches through the birth date column" << endl;
        cout << "Search -c [string] searches through the country column" << endl;
        cout << "Search -C [string] searches through the database case sensitive" << endl;
        cout << "Search -d [string] searches through the death date column" << endl;
        cout << "Search -g [string] searches through the date of gender column" << endl;
        cout << "Search -n [string] searches through the names column" << endl;
        cout << "Search -z [string] returns search in descending order" << endl;
    }
    else if (command == "sort") {
        cout << "Sort/sort -a prints out the database in ascending order." << endl;
        cout << "Sort -d prints out the database in descending order." << endl;
    }
    else if (command == "help") {
        cout << "==================HELP MENU====================" << endl;
        cout << "Type help [keyword] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "The keywords used in this program are: " << endl;
        cout << "[add] is used to add a person to the datebase."  << endl;
        cout << "[display] is used to print out the database." << endl;
        cout << "[search] is used to search for an item in the database." << endl;
        cout << "[sort] is used to sort the list in the database." << endl;
    }
    else {
        cout << "No help found for command: " << command << ". See help menu for instructions:" << endl;
        help("help");
    }
}
