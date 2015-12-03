#include "presentation.h"
#include "domain.h"
#include "person.h"
#include <iomanip>
#include <cstdlib>

using namespace std;

void loop(){
    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    string message = ""; // General use message
    vector<Person> people; // The data vector
    int longestName; // Longest name var
    int currentId; // Current Id

    // Add data
    populateVector(people, message);

    if(message == ""){
        // Get longest name
        longestName = findLongestName(people);

        // Get current id
        currentId = getCurrentId(people);

        // Print
        display(people, longestName);

        // ===== MAIN =====

        while(command != "q" || command != "quit"){
            cout << ">";

            // Get command
            getline(cin, command);

            // Display the vector
            if(command == "list" || command == "ls"){
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
                addProcess(people, currentId);
            }
            // Delete
            else if(getCommand(command) == "delete") {
                message = del(people, command);
                cout << message << endl;
            }
            // Edit
            else if(getCommand(command) == "edit") {
                message = edit(people, command);
                cout << message << endl;
            }
            // Write to database
            else if(command == "save") {
                writeVector(people);
            }
            // Help
            else if(getCommand(command) == "help"){
                help(command);
            }
            // Quit
            else if(command == "q" || command == "quit"){
                break;
            }
            // Clear screen
            else if(command == "clear") {
                clearScreen();
                // system("clear"); is not the way to go appearantly
            }
            // Invalid
            else if(command != ""){
                cout << "Invalid command. Type help for available commands." << endl;
            }
        }
    }
    else{
        cout << message << endl;
    }
}

void addProcess(vector<Person> &p, int currentID){
    string name, gender, dob, dod = "", country;
    bool valid = false;

    // Name
    do{
        cout << "Name: ";
        getline(cin, name);

        if(name == ""){
            cout << "Please enter a name." << endl;
        }
    }while(name == "");

    // Gender
    do{
       cout << "Gender (M/F): ";
       getline(cin, gender);

       gender = verifyGender(gender);

    }while(gender == "" || (gender[0] != 'm' && gender[0] != 'f'));

    // Date of birth
    do{
        cout << "Date of birth (DD/MM/YYYY): ";
        getline(cin, dob);

        valid = verifyDate(dob);

        if(!valid){
            cout << "Invalid date format." << endl;
        }
    }while(!valid);

    // Date of death
    do{
        valid = false;

        cout << "Date of death (DD/MM/YYYY, if alive: -): ";
        getline(cin, dod);

        if(dod == "-"){
            dod = "";
            break;
        }
        else{
            valid = verifyDate(dod);

            if(!valid){
                cout << "Invalid date format." << endl;
            }
        }
    }while(!valid);

    // Country
    do{
        cout << "Country of origin: ";
        getline(cin, country);

        if(country == ""){
            cout << "Please enter a country." << endl;
        }
    }while(country == "");

    // Add + print
    cout << addPerson(p, currentID, name, gender, dob, dod, country) << endl;
}

// Display
void display(vector<Person> p, int longestName){
    cout << "| ";
    cout << left << setw(4) << "ID" << " | ";
    cout << setw(longestName) << "Name" << " | ";
    cout << setw(6) << "Gender" << " | ";
    cout << setw(10) << "Birth date" << " | ";
    cout << setw(10) << "Death date" << " | ";
    cout << setw(4) << "Country" << endl;

    for(int i = 0; i < (TABLE_LENGTH + longestName); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < p.size(); i++){
        cout << "| ";
        cout << setw(4) << p[i].getId() << " | ";
        cout << setw(longestName) << p[i].getName() << " | ";
        cout << setw(6) << p[i].getGender() << " | ";
        cout << setw(10) << p[i].getDateOfBirth() << " | ";
        cout << setw(10) << p[i].getDateOfDeath() << " | ";
        cout << p[i].getCountry() << endl;
    }
    for(int i = 0; i < (TABLE_LENGTH + longestName); i++){
        cout << "-";
    }
    cout << endl << "| Results: " << p.size() << endl;
}

// Clear screen
void clearScreen() {
    for (int i = 0; i < 5; i++) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }
}

// Help
void help(string command) {
    // Remove "help " from string
    (command.length() == 4) ? command = "help" : command = command.erase(0,5);

    // Add
    if (command == "add") {
        cout << "Follow the instructions on the screen." << endl;
    }
    // List
    else if (command == "list" || command == "ls") {
        cout << "Prints the database on the screen." << endl;
        cout << "[list] and [ls] are synonymous" << endl;
    }
    // Search
    else if (command == "search") {
        cout << "search [string] searches through all the columns except gender" << endl;
        cout << "search -a [string] returns search in ascending order" << endl;
        cout << "search -b [string] searches through the birth date column" << endl;
        cout << "search -c [string] searches through the country column" << endl;
        cout << "search -C [string] searches through the database case sensitive" << endl;
        cout << "search -d [string] searches through the death date column" << endl;
        cout << "search -g [string] searches through the date of gender column" << endl;
        cout << "search -i [string] searches through the ID column" << endl;
        cout << "search -n [string] searches through the name column" << endl;
        cout << "search -z [string] returns search in descending order" << endl;
        cout << "search [args] [male|female] searches for specified gender" << endl;
        cout << "Any number of arguements are accepted in any order with the exception of only 1 sorting method defined." << endl;
    }
    // Filter
    else if (command == "filter") {
        cout << "filter [string] filters out the string in all the columns except gender" << endl;
        cout << "filter -a [string] returns filter in ascending order" << endl;
        cout << "filter -b [string] filters out matches in the birth date column" << endl;
        cout << "filter -c [string] filters out matches in the country column" << endl;
        cout << "filter -C [string] filters out matches in the database case sensitive" << endl;
        cout << "filter -d [string] filters out matches in the death date column" << endl;
        cout << "filter -g [string] filters out matches in the date of gender column" << endl;
        cout << "filter -i [string] filters out matches in the ID column" << endl;
        cout << "filter -n [string] filters out matches in the names column" << endl;
        cout << "filter -z [string] returns filter in descending order" << endl;
        cout << "filter [args] [male|female] filter out a specified gender" << endl;
        cout << "Any number of arguements are accepted in any order with the exception of only 1 sorting method defined." << endl;
    }
    // Sort
    else if (command == "sort") {
        cout << "sort/sort -a prints out the database in ascending order by name." << endl;
        cout << "sort -d prints out the database in descending order by name." << endl;
        cout << "sort -i prints out the database in ascending order by ID." << endl;
        cout << "sort -iD prints out the database in descending order by ID." << endl;
    }
    // Delete
    else if (command == "delete") {
        cout << "delete [id] deletes the entry in the database with corresponding id" << endl;
    }
    // Edit
    else if (command == "edit") {
        cout << "edit [field] [id] [value]" << endl;
        cout << "edit -n [id] [value] replaces the name of the person of the specified id with the specified value" << endl;
        cout << "edit -g [id] [value] replaces the gender of the person of the specified id. Accepted values are \"m\",\"male\",\"f\" and \"female\"" << endl;
        cout << "edit -b [id] [value] replaces the birth date of the person of the specified id with the specified date" << endl;
        cout << "edit -d [id] [value] replaces the death date of the person of the specified id with the specified date" << endl;
        cout << "edit -c [id] [value] replaces the country of the person of the specified id with the specified value" << endl;
    }
    // Edit
    else if (command == "quit" || command == "q") {
        cout << "Safely exits the application" << endl;
        cout << "[quit] and [q] are synonymous" << endl;
    }
    // Menu
    else if (command == "help") {
        cout << "==================HELP MENU====================" << endl;
        cout << "Type help [command] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "The command used in this program are: " << endl;
        cout << "[add] is used to add a person to the database."  << endl;
        cout << "[delete] is used to delete a person from database."  << endl;
        cout << "[list] is used to print out the database." << endl;
        cout << "[search] is used to search for an item in the database." << endl;
        cout << "[filter] is used to filter out an item in the database." << endl;
        cout << "[sort] is used to sort the list in the database." << endl;
        cout << "[edit] is used to edit a person's information in the database." << endl;
        cout << "[clear] is used to clear the console window" << endl;
        cout << "[quit] is used to quit the program." << endl;
    }
    // Error
    else {
        cout << "No help found for command: \"" << command << "\"\nSee help menu for instructions:" << endl;
        help("help");
    }
}
