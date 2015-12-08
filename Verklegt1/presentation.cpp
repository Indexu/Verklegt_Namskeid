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
        cout << "Type add -p to add a person and add -m to add a machine." << endl;
        cout << "Follow the instructions on the screen." << endl;
        cout << "Type -1 in any steps to quit." << endl;
    }
    // List menu
    else if (command == "ls") {
        cout << "==================LIST MENU====================" << endl;
        cout << "Type help [command] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "[ls -p] is used to print out list of persons in ascending orders." << endl;
        cout << "[ls -m] is used to print out list of machines in ascending orders." << endl;
        cout << "[ls -pm] is used to print out list of connections between persons and machines in ascending orders." << endl;
    }

    // List options for persons
    else if (command == "ls -p") {
        cout << "===============================================" << endl;
        cout << "For more detailed print options, type: ls -m [field]" << endl;
        cout << "====================[field]==================== " << endl;
        cout << "[-n] to print out orderd by persons names." << endl;
        cout << "[-g] to print out orderd by persons gender." << endl;
        cout << "[-b] to print out orderd by date of birth." << endl;
        cout << "[-e] to print out orderd by date of death." << endl;
        cout << "[-c] to print out orderd by persons countries." << endl;
        cout << "Type [-d] after [field] to print out in descending orders." << endl;
    }

    // List options for machines
    else if (command == "ls -m") {
        cout << "===============================================" << endl;
        cout << "For more detailed print options, type: ls -m [field]" << endl;
        cout << "====================[field]==================== " << endl;
        cout << "[-n] to print out orderd by machine names." << endl;
        cout << "[-y] to print out orderd by machine years." << endl;
        cout << "[-b] to print out orderd by machine built." << endl;
        cout << "[-t] to print out orderd by machine types." << endl;
        cout << "[-s] to print out orderd by machine systems." << endl;
        cout << "Type [-d] after [field] to print out in descending orders." << endl;
    }

    // List options for persons and machines
    else if (command == "ls -pm") {
        cout << "===============================================" << endl;
        cout << "For more detailed print options, type: ls -pm [field]" << endl;
        cout << "====================[field]==================== " << endl;
        cout << "[-p] to print out orderd by persons names." << endl;
        cout << "[-c] to print out orderd by persons countries." << endl;
        cout << "[-m] to print out orderd by machine names." << endl;
        cout << "[-t] to print out orderd by machine types." << endl;
        cout << "[-s] to print out orderd by machine systems." << endl;
        cout << "Type [-d] after [field] to print out in descending orders." << endl;
    }
    // Search menu
    else if (command == "search") {
        cout << "==================SEARCH MENU====================" << endl;
        cout << "Type help [command] for more detailed options." << endl;
        cout << "===============================================" << endl;
        cout << "[search -p] [string] is used to search through all persons except gender." << endl;
        cout << "[search -m] [string] is used to search through all machines." << endl;
        cout << "[search -pm] [string] is used to search through all connections between persons and machines." << endl;
    }

    // Search options for persons
    else if (command == "search -p") {
        cout << "===============================================" << endl;
        cout << "Search -p [field][sort][-d][value]" << endl;
        cout << "====================[field]==================== " << endl;
        cout << "[-n] searches through the name column." << endl;
        cout << "[-g] searches through the gender column." << endl;
        cout << "[-b] searches through the date of birth column." << endl;
        cout << "[-e] searches through the death date column." << endl;
        cout << "[-c] searches through the country column." << endl;
        cout << "====================[sort]==================== " << endl;
        cout << "[-sn] sorts search after name." << endl;
        cout << "[-sg] sorts search after gender." << endl;
        cout << "[-sb] sorts search after date of birth." << endl;
        cout << "[-se] sorts search after date of death." << endl;
        cout << "[-sc] sorts aearch after country." << endl;
        cout << "Type [-d] to sort search in descending orders." << endl;
    }

    // Search options for machines
    else if (command == "search -m") {
        cout << "===============================================" << endl;
        cout << "Search -m [field][sort][-d][value]" << endl;
        cout << "====================[field]==================== " << endl;
        cout << "[-n] searches through the name column." << endl;
        cout << "[-y] searches through the year column." << endl;
        cout << "[-b] searches through the built column." << endl;
        cout << "[-t] searches through the type column." << endl;
        cout << "[-s] searches through the system column." << endl;
        cout << "====================[sort]==================== " << endl;
        cout << "[-sn] sorts search after name." << endl;
        cout << "[-sy] sorts search after year." << endl;
        cout << "[-sb] sorts search after built." << endl;
        cout << "[-st] sorts search after type." << endl;
        cout << "[-ss] sorts aearch after system." << endl;
        cout << "Type [-d] to sort search in descending orders." << endl;
    }

    // Filter menu
    else if (command == "filter") {
        cout << "==================FILTER MENU====================" << endl;
        cout << "[filter -p] [string] is used to filter out all columns in persons." << endl;
        cout << "[filter -m] [string] is used to filter out all columns in machines." << endl;
        cout << "[filter -pm] [string] is used to filter out all connections between persons and machines." << endl;
        cout << "===============================================" << endl;
        cout << "Filter works like a reverse search. It uses the same [field] and [sort] as search." << endl;
     }

    // Delete
    else if (command == "delete") {
        cout << "delete [-p] [p_id] deletes the entry in the persons database with corresponding id." << endl;
        cout << "delete [-m] [m_id] deletes the entry in the machines database with corresponding id." << endl;
        cout << "delete [-pm] [pm_id] deletes the entry in the person and machine connection database with corresponding id." << endl;
    }

    // Edit
    else if (command == "edit") {
        cout << "==================EDIT MENU====================" << endl;
        cout << "edit [table] [field] [id] [value]" << endl;
        cout << "===============================================" << endl;
        cout << "edit -p -n [id] [value] replaces the name of the person of the specified id with the specified value." << endl;
        cout << "edit -p -g [id] [value] replaces the gender of the person of the specified id. Accepted values are \"m\",\"male\",\"f\" and \"female\"" << endl;
        cout << "edit -p -b [id] [value] replaces the birth date of the person of the specified id with the specified date." << endl;
        cout << "edit -p -d [id] [value] replaces the death date of the person of the specified id with the specified date." << endl;
        cout << "edit -p -c [id] [value] replaces the country of the person of the specified id with the specified value." << endl << endl;
        cout << "edit -m -n [id] [value] replaces the name of the machine of the specified id with the specified value." << endl;
        cout << "edit -m -y [id] [value] replaces the year of the machine of the specified id with the specified value." << endl;
        cout << "edit -m -b [id] [value] replaces the built of the machine of the specified id. Accepted values are \"y\",\yes\", \"n\" and \"no\"" << endl;
        cout << "edit -m -t [id] [value] replaces the type of the machine of the specified id. Accepted value for type are ID that already exist." << endl;
        cout << "edit -m -s [id] [value] replaces the system of the machine of the specified id. Accepted value for system are ID that already exist." << endl;
    }

    // Edit
    else if (command == "quit" || command == "q") {
        cout << "Safely exits the application." << endl;
        cout << "[quit] and [q] are synonymous." << endl;
    }

    //Con
    else if (command == "con"){
        cout << "con [ID person] [ID machine] to connect together machine and person." << endl;
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
        cout << "[con] is used to connect together machine and person." << endl;
        cout << "[clear] is used to clear the console window." << endl;
        cout << "[quit] is used to quit the program." << endl;
    }

    // Error
    else {
        cout << "No help found for command: \"" << command << "\"\nSee help menu for instructions:" << endl;
        help("help");
    }
}
