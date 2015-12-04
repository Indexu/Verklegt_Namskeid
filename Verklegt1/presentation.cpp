#include "presentation.h"
#include "domain.h"
#include "person.h"
#include "machine.h"
#include "utility.h"
#include "data.h"
#include <iomanip>
#include <cstdlib>

using namespace std;

void loop(){
    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    string message = ""; // General use message
    vector<Person> people; // The person vector
    vector<Machine> machines; // The machine vector
    int longestName; // Longest name var
    int currentId; // Current Id

    // Connect to DB
    message = startDB();

    if(message == ""){
        // Add data
        message = populatePersonVector(people, "");

        if(message == ""){
            message = populateMachineVector(machines, "");

            if(message == ""){
                // Get longest name
                longestName = findLongestName(people);

                // Get current id
                currentId = getCurrentId(people);

                // Print
                displayPerson(people, longestName);

                // ===== MAIN =====

                while(command != "q" || command != "quit"){
                    cout << ">";

                    // Get command
                    getline(cin, command);

                    // List
                    if(getCommand(command) == "ls"){

                        // If only "ls"
                        if(command == "ls"){
                            cout << "Missing flag" << endl;
                        }
                        // List - People
                        else if(command.substr(0,5) == "ls -p"){
                            // Get persons
                            people = listPersons(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display people
                                displayPerson(people, longestName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

                        }
                        // List - Machines
                        else if(command.substr(0,5) == "ls -m"){
                            /*
                            // Get machines
                            people = listPersons(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display machines
                                display(people, longestName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }*/

                        }
                        else{
                            cout << "Invalid flag: \"" << command.substr(4,2) << "\"" << endl;
                        }


                    }
                    // Filter
                    else if(getCommand(command) == "filter"){
                        if (command == "filter") {
                            message = "Filter command is missing flags. See help for instructions.";
                            cout << message << endl;
                        }
                        else if (command.substr(0,9) == "filter -p") {
                            vector<Person> results = filter(command, message);
                            if (message == "") {
                                displayPerson(results, longestName);
                            }
                            else {
                                cout << message << endl;
                            }
                        }
                        else if (command.substr(0,9) == "filter -m") {
                            message = "DB_Machine not ready yet. Try filter -p for persons.";
                            cout << message;
                        }
                        else {
                            message = "First flag is invalid! Available flags are: -p for person, -m for machines.";
                            cout << message << endl;
                        }
                    }
                    // Add
                    else if(command == "add") {
                        addProcess(people);
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
                    // Search
                    else if(getCommand(command) == "search"){
                        if (command == "search") {
                            message = "Search command is missing flags. See help for instructions.";
                            cout << message << endl;
                        }
                        else if (command.substr(0,9) == "search -p") {
                            vector<Person> results = callSearchPersonDB(command, message);
                            if (message == "") {
                                displayPerson(results, longestName);
                            }
                            else {
                                cout << message << endl;
                            }
                        }
                        else if (command.substr(0,9) == "search -m") {
                            message = "DB_Machine not ready yet. Try search -p for persons.";
                            cout << message;
                        }
                        else {
                            message = "First flag is invalid! Available flags are: -p for person, -m for machines.";
                            cout << message << endl;
                        }
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
        else{
            cout << message << endl;
        }
    }
    else{
        cout << message << endl;
    }
}

void addProcess(vector<Person> &p){
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
    cout << addPerson(p, name, gender, dob, dod, country) << endl;
}

// Display
void displayPerson(vector<Person> p, int longestName){
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
    else if (command == "ls") {
        cout << "ls -p prints out all persons ordered by ID in ascending order" << endl;
        cout << "ls -p -d prints out all persons ordered by ID in descending order" << endl;
        cout << "ls -p -a prints out all persons ordered by name in ascending order" << endl;
        cout << "ls -p -z prints out all persons ordered by name in descending order" << endl;
        cout << "ls -m prints out all machines ordered by ID in ascending order" << endl;
        cout << "ls -m -d prints out all machines ordered by ID in descending order" << endl;
        cout << "ls -m -a prints out all machines ordered by name in ascending order" << endl;
        cout << "ls -m -z prints out all machines ordered by name in descending order" << endl;
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
        cout << "[ls] is used to print out the database." << endl;
        cout << "[search] is used to search for an item in the database." << endl;
        cout << "[filter] is used to filter out an item in the database." << endl;
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
