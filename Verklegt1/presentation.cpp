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

        while(command != "q" || command != "quit"){
            cout << ">";

            // Get command
            getline(cin, command);

            // Display the vector
            if(command == "display" || command == "list"){
                display(people, longestName);
            }
            // Sort
            else if(getCommand(command) == "sort"){
                sortNames(people, command);
                display(people, longestName);
            }
            // Search
            else if(getCommand(command) == "search"){
                vector<Person> results = search(people, command, message);
                if(message == ""){
                    display(results, longestName);
                }
                else{
                    cout << message << endl;
                }
            }
            // Filter
            else if(getCommand(command) == "filter"){
                vector<Person> results = filter(people, command, message);
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
            else if(command == "q" || command == "quit"){
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
        cout << "| ";
        cout << setw(longestName) << p[i].getName() << " | ";
        cout << setw(6) << p[i].getGender() << " | ";
        cout << setw(10) << p[i].getDateOfBirth() << " | ";
        cout << setw(10) << p[i].getDateOfDeath() << " | ";
        cout << p[i].getCountry() << endl;
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
        cout << "search [string] searches through all the columns except gender" << endl;
        cout << "search -a [string] returns search in ascending order" << endl;
        cout << "search -b [string] searches through the birth date column" << endl;
        cout << "search -c [string] searches through the country column" << endl;
        cout << "search -C [string] searches through the database case sensitive" << endl;
        cout << "search -d [string] searches through the death date column" << endl;
        cout << "search -g [string] searches through the date of gender column" << endl;
        cout << "search -n [string] searches through the names column" << endl;
        cout << "search -z [string] returns search in descending order" << endl;
        cout << "search [args] [male|female] searches for specified gender" << endl;
        cout << "Any number of arguements are accepted in any order with the exception of only 1 sorting method defined." << endl;
    }
    else if (command == "filter") {
        cout << "filter [string] filters out the string in all the columns except gender" << endl;
        cout << "filter -a [string] returns filter in ascending order" << endl;
        cout << "filter -b [string] filters out matches in the birth date column" << endl;
        cout << "filter -c [string] filters out matches in the country column" << endl;
        cout << "filter -C [string] filters out matches in the database case sensitive" << endl;
        cout << "filter -d [string] filters out matches in the death date column" << endl;
        cout << "filter -g [string] filters out matches in the date of gender column" << endl;
        cout << "filter -n [string] filters out matches in the names column" << endl;
        cout << "filter -z [string] returns filter in descending order" << endl;
        cout << "filter [args] [male|female] filter out a specified gender" << endl;
        cout << "Any number of arguements are accepted in any order with the exception of only 1 sorting method defined." << endl;
    }
    else if (command == "sort") {
        cout << "sort/sort -a prints out the database in ascending order." << endl;
        cout << "sort -d prints out the database in descending order." << endl;
    }
    else if (command == "help") {
        cout << "==================HELP MENU====================" << endl;
        cout << "Type help [command] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "The command used in this program are: " << endl;
        cout << "[add] is used to add a person to the datebase."  << endl;
        cout << "[display] is used to print out the database." << endl;
        cout << "[search] is used to search for an item in the database." << endl;
        cout << "[filter] is used to filter out an item in the database." << endl;
        cout << "[sort] is used to sort the list in the database." << endl;
    }
    else {
        cout << "No help found for command: \"" << command << "\"\nSee help menu for instructions:" << endl;
        help("help");
    }
}
