#include "presentation.h"
#include "domain.h"
#include "person.h"
#include "machine.h"
#include "utility.h"
#include "data.h"
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;

void loop(){
    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    string message = ""; // General use message
    vector<Person> people; // The person vector
    vector<Machine> machines; // The machine vector
    vector<TypeSystem> types, systems; // Types and systems vectors
    vector<PersonMachine> pers_mach; // Person Machine vector
    int longestPName; // Longest person name
    int longestMName; // Longest machine name
    int longestMType; // Longest machine type
    int longestTName; // Longest type name
    int longestSName; // Longest system name
    int currentId; // Current Id

    // Connect to DB
    message = startDB();

    if(message == ""){
        // Add data to persons vector
        message = populatePersonVector(people, ' ', false);

        if(message == ""){
            // Add data to machines vector
            message = populateMachineVector(machines, ' ', false);

            // Add data to types vector
            if(message == ""){
                message = populateTSVector(types, 't', ' ', false);
            }

            // Add vector to systems vector
            if(message == ""){
                message = populateTSVector(systems, 's', ' ', false);
            }

            // Add vector to pers_mach vector
            if(message == ""){
                message = populatePMVector(pers_mach, ' ', false);
            }

            if(message == ""){
                // Get longest everything
                longestPName = findLongestPName(people);
                longestMName = findLongestMName(machines);
                longestMType = findLongestMType(machines);
                longestTName = findLongestTSName(types);
                longestSName = findLongestTSName(systems);

                // Get current id
                currentId = getCurrentId(people);

                // Print
                displayPerson(people, longestPName);

                // ===== MAIN =====

                while(command != "q" || command != "quit"){
                    // Reset message
                    message = "";

                    cout << ">";

                    // Get command
                    getline(cin, command);

                    // List
                    if(getCommand(command) == "ls"){

                        // If only "ls"
                        if(command == "ls"){
                            cout << "Missing flag" << endl;
                        }
                        // List - Person and Machines
                        else if(command.substr(0,6) == "ls -pm"){

                            // Get persons and machines
                            pers_mach = listPM(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display persons and machines
                                displayPersonsMachines(pers_mach, longestPName, longestMName, longestMType, longestSName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

                        }
                        // List - People
                        else if(command.substr(0,5) == "ls -p"){
                            // Get persons
                            people = listPersons(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display people
                                displayPerson(people, longestPName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

                        }
                        // List - Machines
                        else if(command.substr(0,5) == "ls -m"){

                            // Get machines
                            machines = listMachines(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display machines
                                displayMachine(machines, longestMName, longestMType);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

                        }
                        // List - Types
                        else if(command.substr(0,5) == "ls -t"){

                            // Get types
                            types = listTS(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display types
                                displayTS(types, longestTName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

                        }
                        // List - Systems
                        else if(command.substr(0,5) == "ls -s"){

                            // Get types
                            systems = listTS(command, message);

                            // Check for errors
                            if(message == ""){
                                // Display types
                                displayTS(systems, longestSName);
                            }
                            else{
                                // Display errors
                                cout << message << endl;
                            }

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
                                displayPerson(results, longestPName);
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
                    else if(getCommand(command) == "add") {
                        // Only "add"
                        if(command == "add"){
                            cout << "Add command is missing a flag. See help for instructions." << endl;
                        }
                        // Add person
                        else if(command.substr(0,9) == "add -p"){
                            addProcessPerson(people);
                        }
                        // Add machine
                        else if(command.substr(0,9) == "add -m"){
                            addProcessMachine(machines, types, systems);
                        }
                        // Invalid flag
                        else{
                            cout << "Flag is invalid! Available flags are: -p for person, -m for machines." << endl;
                        }

                    }
                    // Delete
                    else if(getCommand(command) == "delete") {
                        // Only "delete"
                        if(command == "delete"){
                            cout << "Delete command is missing flags. See help for instructions." << endl;
                        }
                        // Delete person
                        else if(command.substr(0,10) == "delete -pm"){
                            message = delPM(pers_mach, command);

                            if(message != ""){
                                cout << message << endl;
                            }
                        }
                        // Delete person
                        else if(command.substr(0,9) == "delete -p"){
                            message = delPerson(people, command);

                            if(message != ""){
                                cout << message << endl;
                            }
                        }
                        // Delete machine
                        else if(command.substr(0,9) == "delete -m"){
                            message = delMachine(machines, command);

                            if(message != ""){
                                cout << message << endl;
                            }
                        }
                        // Invalid flag
                        else{
                            cout << "First flag is invalid! Available flags are: -p for person, -m for machines." << endl;
                        }

                    }
                    // Edit
                    else if(getCommand(command) == "edit") {
                        // Only "edit"
                        if(command == "edit"){
                            cout << "Edit command is missing flags. See help for instructions." << endl;
                        }
                        // Edit person
                        else if(command.substr(0,7) == "edit -p"){
                            message = editPerson(people, command);

                            if(message != ""){
                                cout << message << endl;
                            }
                        }
                        // Edit machine
                        else if(command.substr(0,7) == "edit -m"){
                            message = editMachine(machines, command);

                            if(message != ""){
                                cout << message << endl;
                            }
                        }
                        // Invalid flag
                        else{
                            cout << "First flag is invalid! Available flags are: -p for person, -m for machines." << endl;
                        }
                    }
                    // Connect
                    else if(getCommand(command) == "con") {
                        // Only "con"
                        if(command == "con"){
                            cout << "Con command is missing ID's. See help for instructions." << endl;
                        }
                        else{
                            cout << conPM(people, machines, command) << endl;
                        }
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
                        // Search not specified
                        if (command == "search") {
                            message = "Search command is missing flags. See help for instructions.";
                            cout << message << endl;
                        }
                        // Searches through persons database
                        else if (command.substr(0,9) == "search -p") {
                            vector<Person> results = callSearchPersonDB(command, message);
                            if (message == "") {
                                displayPerson(results, longestPName);
                            }
                            else {
                                cout << message << endl;
                            }
                        }
                        // Searches through machine database
                        else if (command.substr(0,9) == "search -m") {
                            vector<Machine> results = callSearchMachineDB(command, message);
                            if (message == "") {
                                displayMachine(results, longestMName, longestMType);
                            }
                            else {
                                cout << message << endl;
                            }
                        }
                        // Error message if invalid database is specified
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

// Add process for persons
void addProcessPerson(vector<Person> &p){
    string name, gender, dob, dod = "", country;
    bool valid = false;

    // Input to cancel
    string cancel = "-1";

    // Name
    do{
        cout << "Name: ";
        getline(cin, name);

        if(name == ""){
            cout << "Please enter a name." << endl;
        }
        else if(name == cancel){
            return;
        }
    }while(name == "");

    // Gender
    do{
        cout << "Gender (M/F): ";
        getline(cin, gender);

        if(gender == cancel){
            return;
        }

       gender = verifyGender(gender);

    }while(gender == "" || (gender[0] != 'm' && gender[0] != 'f'));

    // Date of birth
    do{
        cout << "Date of birth (YYYY-MM-DD): ";
        getline(cin, dob);

        if(dob == cancel){
            return;
        }

        valid = verifyDate(dob);

        if(!valid){
            cout << "Invalid date format." << endl;
        }
    }while(!valid);

    // Date of death
    do{
        valid = false;

        cout << "Date of death (YYYY-MM-DD, if alive: -): ";
        getline(cin, dod);

        if(dod == "-"){
            dod = "";
            break;
        }
        else if(dod == cancel){
            return;
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
        else if(country == cancel){
            return;
        }
    }while(country == "");

    // Add + print
    cout << addPerson(p, name, gender, dob, dod, country) << endl;
}

// Add process for machines
void addProcessMachine(vector<Machine> &m, const vector<TypeSystem> &t, const vector<TypeSystem> &s){
    string name, built, year, type, system;
    int typeInt, systemInt;

    // Input to cancel
    string cancel = "-1";

    // Name
    do{
        cout << "Name: ";
        getline(cin, name);

        if(name == ""){
            cout << "Please enter a name." << endl;
        }
        else if(name == cancel){
            return;
        }
    }while(name == "");

    // Year
    do{
        cout << "Year built (YYYY, \"-\" if unknown/not built): ";
        getline(cin, year);

        if(year == cancel){
            return;
        }
        else if(year == "-"){
            year = "0";
            break;
        }
        else if(year == ""){
            cout << "Please enter a year." << endl;
        }
        else if(year.length() != 4 && year != "0"){
            cout << "Invalid year." << endl;
        }

    }while(year == "" || year == "0" || year.length() != 4);

    // Built
    do{
        cout << "Built (y/n): ";
        getline(cin, built);

        if(built == cancel){
            return;
        }
        else if(built == ""){
            cout << "Please enter \"y\" or \"n\"." << endl;
        }
        else if(built == "y"){
            built = "true";
            break;
        }
        else if(built == "n"){
            built = "false";
            break;
        }

    }while(built == "" || (built != "y" && built != "n"));

    // Type
    do{
        // Print options
        for(int i = 0; i < (int)t.size(); i++){
            cout << t[i].getId() << ". " << t[i].getName() << endl;
        }

        cout << "Enter number of corresponding type: ";
        getline(cin, type);

        if(type == cancel){
            return;
        }
        else if(type == ""){
            cout << "Please enter a type." << endl;
        }
        else if(isNumber(type)){
            typeInt = stoi(type);

            if(typeInt <= (int)t.size() && typeInt >= 1){
                break;
            }
            else{
                cout << "Please enter a number in the list." << endl;
            }
        }
        else{
            cout << "Please enter a number in the list." << endl;
        }
    }while(type == "" || typeInt > (int)t.size() || typeInt < 1);

    // System
    do{
        // Print options
        for(int i = 0; i < (int)s.size(); i++){
            cout << s[i].getId() << ". " << s[i].getName() << endl;
        }

        cout << "Enter number of corresponding system: ";
        getline(cin, system);

        if(system == cancel){
            return;
        }
        else if(system == ""){
            cout << "Please enter a system." << endl;
        }
        else if(isNumber(system)){
            systemInt = stoi(system);

            if(systemInt <= (int)s.size() && systemInt >= 1){
                break;
            }
            else{
                cout << "Please enter a number in the list." << endl;
            }
        }
        else{
            cout << "Please enter a number in the list." << endl;
        }
    }while(system == "" || systemInt > (int)s.size() || systemInt < 1);

    // Add + print
    cout << addMachine(m, name, year, built, type, system) << endl;
}

// Display Persons
void displayPerson(vector<Person> p, int longestPName){
    cout << "| ";
    cout << left << setw(4) << "ID" << " | ";
    cout << setw(longestPName) << "Name" << " | ";
    cout << setw(6) << "Gender" << " | ";
    cout << setw(10) << "Birth date" << " | ";
    cout << setw(10) << "Death date" << " | ";
    cout << setw(4) << "Country" << endl;

    for(int i = 0; i < (TABLE_LENGTH + longestPName); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < p.size(); i++){
        cout << "| ";
        cout << setw(4) << p[i].getId() << " | ";
        cout << setw(longestPName) << p[i].getName() << " | ";
        cout << setw(6) << p[i].getGender() << " | ";
        cout << setw(10) << p[i].getDateOfBirth() << " | ";
        cout << setw(10) << p[i].getDateOfDeath() << " | ";
        cout << p[i].getCountry() << endl;
    }
    for(int i = 0; i < (TABLE_LENGTH + longestPName); i++){
        cout << "-";
    }
    cout << endl << "| Results: " << p.size() << endl;
}

// Display Machines
void displayMachine(const vector<Machine> &m, const int &longestMName, const int &longestMType){
    cout << "| ";
    cout << left << setw(4) << "ID" << " | ";
    cout << setw(longestMName) << "Name" << " | ";
    cout << setw(6) << "Year" << " | ";
    cout << setw(5) << "Built" << " | ";
    cout << setw(longestMType) << "Type" << " | ";
    cout << setw(4) << "System" << endl;

    for(int i = 0; i < (TABLE_LENGTH + longestMName + longestMType); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < m.size(); i++){
        cout << "| ";
        cout << setw(4) << m[i].getId() << " | ";
        cout << setw(longestMName) << m[i].getName() << " | ";
        cout << setw(6) << m[i].getYear() << " | ";
        cout << setw(5) << boolYesNo(m[i].getBuilt()) << " | ";
        cout << setw(longestMType) << m[i].getType() << " | ";
        cout << setw(4) << m[i].getSystem() << endl;
    }
    for(int i = 0; i < (TABLE_LENGTH + longestMName + longestMType); i++){
        cout << "-";
    }
    cout << endl << "| Results: " << m.size() << endl;
}

// Display types and systems
void displayTS(const vector<TypeSystem> &ts, const int &longestName){
    cout << "| ";
    cout << left << setw(4) << "ID" << " | ";
    cout << setw(longestName) << "Name" << " | " << endl;

    for(int i = 0; i < (TABLE_LENGTH + longestName); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < ts.size(); i++){
        cout << "| ";
        cout << setw(4) << ts[i].getId() << " | ";
        cout << setw(longestName) << ts[i].getName() << " | " << endl;
    }
    for(int i = 0; i < (TABLE_LENGTH + longestName); i++){
        cout << "-";
    }
    cout << endl << "| Results: " << ts.size() << endl;
}

// Display Persons and Machines
void displayPersonsMachines(vector<PersonMachine> pm, int longestPName, int longestMName, int longestMType, int longestSName){
    cout << "| ";
    cout << left << setw(4) << "ID" << " | ";
    cout << setw(longestPName) << "Person" << " | ";
    cout << setw(longestMName) << "Machine" << " | ";
    cout << setw(longestMType) << "Type" << " | ";
    cout << setw(longestSName) << "System" << " | ";
    cout << setw(4) << "Country" << endl;

    for(int i = 0; i < (TABLE_LENGTH + longestPName + longestMName + longestMType); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < pm.size(); i++){
        cout << "| ";
        cout << left << setw(4) << pm[i].getId() << " | ";
        cout << setw(longestPName) << pm[i].getP_Name() << " | ";
        cout << setw(longestMName) << pm[i].getM_Name() << " | ";
        cout << setw(longestMType) << pm[i].getM_Type() << " | ";
        cout << setw(longestSName) << pm[i].getM_System() << " | ";
        cout << setw(4) << pm[i].getP_Country() << endl;
    }
    for(int i = 0; i < (TABLE_LENGTH + longestPName + longestMName + longestMType); i++){
        cout << "-";
    }
    cout << endl << "| Results: " << pm.size() << endl;
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
        cout << "==================SEARCH MENU====================" << endl;
        cout << "Type help [command] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "[search -p] is used to search through all persons except gender" << endl;
        cout << "[search -m] is used to search through all machines" << endl;
        /*cout << "search -a [string] returns search in ascending order" << endl;
        cout << "search -p -b [string] searches through the birth date column in persons" << endl;
        cout << "search -c [string] searches through the country column" << endl;
        cout << "search -C [string] searches through the database case sensitive" << endl;
        cout << "search -d [string] searches through the death date column" << endl;
        cout << "search -g [string] searches through the date of gender column" << endl;
        cout << "search -i [string] searches through the ID column" << endl;
        cout << "search -n [string] searches through the name column" << endl;
        cout << "search -z [string] returns search in descending order" << endl;
        cout << "search [args] [male|female] searches for specified gender" << endl;
        cout << "Any number of arguements are accepted in any order with the exception of only 1 sorting method defined." << endl;*/
    }

    // Search options for persons
    else if (command == "search -p") {
        //Unfinished
    }

    // Search options for machines
    else if (command == "search -m") {
        //Unfinished
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
