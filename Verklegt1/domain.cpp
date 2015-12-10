#include "domain.h"
#include "data.h"
#include "person.h"
#include "machine.h"
#include "utility.h"
#include <vector>

using namespace std;

// ===== POPULATE PERSON VECTOR =====
string populatePersonVector(vector<Person> &p, const char &sortColumn, const bool &desc){
    return getPersonsDB(p, sortColumn, desc);
}

// ===== POPULATE MACHINE VECTOR =====
string populateMachineVector(vector<Machine> &m, const char &sortColumn, const bool &desc){
    return getMachinesDB(m, sortColumn, desc);
}

// ===== POPULATE TYPES AND SYSTEMS VECTOR =====
string populateTSVector(vector<TypeSystem> &ts, const char &table, const char &sortColumn, const bool &desc){
    return getTSDB(ts, table, sortColumn, desc);
}

// ===== POPULATE PERSON MACHINE VECTOR =====
string populatePMVector(vector<PersonMachine> &pm, const char &sortColumn, const bool &desc){
    return getPersonMachineDB(pm, sortColumn, desc);
}

// ===== LIST =====
// Persons
vector<Person> listPersons(string &command, string &message){
    vector<Person> p;
    bool desc = false; // Descending flag
    char sortColumn = ' '; // Which column to order by

    // Erase "ls -p "
    command = command.erase(0,6);

    // Split
    vector<string> split = splitString(command, " ");

    // Size check
    if(split.size() > 2){
        message = "Invalid ls command. See help for instructions.";
        return p;
    }
    // Check descending flag
    else if(split.size() == 2){
        // If flags are the same
        if(split[0] == split[1]){
            message = "Flags cannot be the same. See help for instructions.";
            return p;
        }
        // If -d is first
        else if(split[0] == "-d"){
            split.erase(split.begin() + 0);
            desc = true;
        }
        // If -d is second
        else if(split[1] == "-d"){
            split.erase(split.begin() + 1);
            desc = true;
        }
        // If -d is neither
        else{
            message = "Invalid ls command. See help for instructions.";
            return p;
        }
    }

    // Check column flag
    if(split.size() == 1){
        if(split[0] == "-n"){
            sortColumn = 'n';
        }
        else if(split[0] == "-d"){
            sortColumn = 'd';
        }
        else if(split[0] == "-d"){
            sortColumn = 'd';
        }
        else if(split[0] == "-g"){
            sortColumn = 'g';
        }
        else if(split[0] == "-c"){
            sortColumn = 'c';
        }
        else if(split[0] == "-b"){
            sortColumn = 'b';
        }
        else if(split[0] == "-e"){
            sortColumn = 'e';
        }
        else if(split[0] == ""){
            sortColumn = ' ';
        }
        else{
            message = "Invalid flag: \"" + command + "\"";
            return p;
        }
    }

    // Run
    populatePersonVector(p, sortColumn, desc);

    return p;
}

// Machines
vector<Machine> listMachines(string &command, string &message){
    vector<Machine> m;

    bool desc = false; // Descending flag
    char sortColumn = ' '; // Which column to order by

    // Erase "ls -m "
    command = command.erase(0,6);

    // Split
    vector<string> split = splitString(command, " ");

    // Size check
    if(split.size() > 2){
        message = "Invalid ls command. See help for instructions.";
        return m;
    }
    // Check descending flag
    else if(split.size() == 2){
        // If flags are the same
        if(split[0] == split[1]){
            message = "Flags cannot be the same. See help for instructions.";
            return m;
        }
        // If -d is first
        else if(split[0] == "-d"){
            split.erase(split.begin() + 0);
            desc = true;
        }
        // If -d is second
        else if(split[1] == "-d"){
            split.erase(split.begin() + 1);
            desc = true;
        }
        // If -d is neither
        else{
            message = "Invalid ls command. See help for instructions.";
            return m;
        }
    }

    // Check column flag
    if(split.size() == 1){
        if(split[0] == "-n"){
            sortColumn = 'n';
        }
        else if(split[0] == "-d"){
            sortColumn = 'd';
            desc = true;
        }
        else if(split[0] == "-d"){
            sortColumn = 'd';
        }
        else if(split[0] == "-y"){
            sortColumn = 'y';
        }
        else if(split[0] == "-b"){
            sortColumn = 'b';
        }
        else if(split[0] == "-t"){
            sortColumn = 't';
        }
        else if(split[0] == "-s"){
            sortColumn = 's';
        }
        else if(split[0] == ""){
            sortColumn = ' ';
        }
        else{
            message = "Invalid flag: \"" + command + "\"";
            return m;
        }
    }

    // Run
    populateMachineVector(m, sortColumn, desc);

    return m;
}

// Types and systems
vector<TypeSystem> listTS(string &command, string &message){
    vector<TypeSystem> ts;

    bool desc = false; // Descending flag
    char sortColumn = ' '; // Which column to order by
    char table = ' ';

    // Erase "ls "
    command = command.erase(0,3);

    // Split
    vector<string> split = splitString(command, " ");
    // 0. table

    // Size check
    if(split.size() > 3){
        message = "Invalid ls command. See help for instructions.";
        return ts;
    }
    // Check descending flag
    else if(split.size() == 3){
        // If flags are the same
        if(split[1] == split[2]){
            message = "Flags cannot be the same. See help for instructions.";
            return ts;
        }
        // If -d is first
        else if(split[1] == "-d"){
            split.erase(split.begin() + 1);
            desc = true;
        }
        // If -d is second
        else if(split[2] == "-d"){
            split.erase(split.begin() + 2);
            desc = true;
        }
        // If -d is neither
        else{
            message = "Invalid ls command. See help for instructions.";
            return ts;
        }
    }

    // Check column flag
    if(split.size() == 2){
        if(split[1] == "-n"){
            sortColumn = 'n';
        }
        else if(split[1] == "-d"){
            sortColumn = 'd';
            desc = true;
        }
        else if(split[1] == ""){
            sortColumn = ' ';
        }
        else{
            message = "Invalid flag: \"" + command + "\"";
            return ts;
        }
    }

    if(split[0] == "-t"){
        table = 't';
    }
    else{
        table = 's';
    }

    // Run
    populateTSVector(ts, table, sortColumn, desc);

    return ts;
}

// Persons and machines
vector<PersonMachine> listPM(string &command, string &message){
    vector<PersonMachine> pm;

    bool desc = false; // Descending flag
    char sortColumn = ' '; // Which column to order by

    // Erase "ls -pm "
    command = command.erase(0,7);

    // Split
    vector<string> split = splitString(command, " ");

    // Size check
    if(split.size() > 2){
        message = "Invalid ls command. See help for instructions.";
        return pm;
    }
    // Check descending flag
    else if(split.size() == 2){
        // If flags are the same
        if(split[0] == split[1]){
            message = "Flags cannot be the same. See help for instructions.";
            return pm;
        }
        // If -d is first
        else if(split[0] == "-d"){
            split.erase(split.begin() + 0);
            desc = true;
        }
        // If -d is second
        else if(split[1] == "-d"){
            split.erase(split.begin() + 1);
            desc = true;
        }
        // If -d is neither
        else{
            message = "Invalid ls command. See help for instructions.";
            return pm;
        }
    }

    // Check column flag
    if(split.size() == 1){
        if(split[0] == "-p"){
            sortColumn = 'p';
        }
        else if(split[0] == "-m"){
            sortColumn = 'm';
        }
        else if(split[0] == "-c"){
            sortColumn = 'c';
        }
        else if(split[0] == "-t"){
            sortColumn = 't';
        }
        else if(split[0] == "-s"){
            sortColumn = 's';
        }
        else if(split[0] == ""){
            sortColumn = ' ';
        }
        else{
            message = "Invalid flag: \"" + command + "\"";
            return pm;
        }
    }

    // Run
    populatePMVector(pm, sortColumn, desc);

    return pm;
}

// ===== SEARCH =====
// Person search
vector<Person> callSearchPersonDB(string &query, string &message,  const bool &filter) {
    // Result vector
    vector<Person> results;
    // Reset message
    message = "";
    // Field flag
    string arg = "";
    // Sorting flag
    string sort = "";
    // Search string
    string searchString = "";
    // Bool for descending
    bool desc = false;

    // Erase command + -p/-m
    query.erase(0,10);

    // Get arguments from the vector
    vector<string> arguments = getArgs(query);

    // Parse command
    message = parseSearchArgs(query, searchString, arguments, arg, sort, desc, "person");
    // Parse error check
    if(message != ""){
        return results;
    }

    // Sort to field
    sort = convert2Field(sort, "person");

    // Error checks
    if(arg == "-1"){
        message = "Invalid field option";
        return results;
    }
    else if(sort == "-1"){
        message = "Invalid sort option";
        return results;
    }
    else if(searchString == "" && !filter){
        message = "Missing search query";
        return results;
    }

    // Run
    results = searchPersonDB(searchString, message, arg, sort, desc);

    // Check errors
    if(message == ""){
        if (results.empty()) {
            message = "No entries matched your search.";
        }
    }
    return results;
}

// Machine search
vector<Machine> callSearchMachineDB(string &query, string &message, const bool &filter) {
    // Result vector
    vector<Machine> results;
    // Reset message
    message = "";
    // Field flag
    string arg = "";
    // Sorting flag
    string sort = "";
    // Search string
    string searchString = "";
    // Bool for descending
    bool desc = false;

    // Erase command + -p/-m
    query.erase(0,10);

    // Get arguments from the vector
    vector<string> arguments = getArgs(query);

    // Parse command
    message = parseSearchArgs(query, searchString, arguments, arg, sort, desc, "machine");
    // Parse error check
    if(message != ""){
        return results;
    }

    // Sort to field
    sort = convert2Field(sort, "machine");

    // Error checks
    if(arg == "-1"){
        message = "Invalid field option";
        return results;
    }
    else if(sort == "-1"){
        message = "Invalid sort option";
        return results;
    }
    else if(searchString == "" && !filter){
        message = "Missing search query";
        return results;
    }

    // Run
    results = searchMachineDB(searchString, message, arg, sort, desc);

    // Check errors
    if(message == ""){
        if (results.empty()) {
            message = "No entries matched your search.";
        }
    }
    return results;
}
// Person-machine search
vector<PersonMachine> callSearchPMDB(string &query, string &message, const bool &filter) {
    // Result vector
    vector<PersonMachine> results;
    // Reset message
    message = "";
    // Field flag
    string arg = "";
    // Sorting flag
    string sort = "";
    // Search string
    string searchString = "";
    // Bool for descending
    bool desc = false;

    // Erase command + -pm
    query.erase(0,11);

    // Get arguments from the vector
    vector<string> arguments = getArgs(query);

    // Parse command
    message = parseSearchArgs(query, searchString, arguments, arg, sort, desc, "PM");
    // Parse error check
    if(message != ""){
        return results;
    }

    // Sort to field
    sort = convert2Field(sort, "PM");

    // Error checks
    if(arg == "-1"){
        message = "Invalid field option";
        return results;
    }
    else if(sort == "-1"){
        message = "Invalid sort option";
        return results;
    }
    else if(searchString == "" && !filter){
        message = "Missing search query";
        return results;
    }

    // Run
    results = searchPMDB(searchString, message, arg, sort, desc);

    // Check errors
    if(message == ""){
        if (results.empty()) {
            message = "No entries matched your search.";
        }
    }
    return results;
}

// ===== Filter =====
// Person filter
vector<Person> filterPerson(string &query, string &message){
    // No value command
    string noValCommand = getNoValueCommand(query);

    // Search
    vector<Person> results = callSearchPersonDB(query, message, false);

    if(message != ""){
        return results;
    }

    // Everyone
    vector<Person> p = callSearchPersonDB(noValCommand, message, true);

    if(message == ""){
        // Whether or not add the person
        bool addPerson;

        for(unsigned int i = 0; i < p.size(); i++){
            addPerson = true;
            // Check search results
            if(results.size() != 0){
                for(unsigned int j = 0; j < results.size(); j++){
                    // Remove search match and do not add the person
                    if(p[i] == results[j]){
                        results.erase(results.begin() + j);
                        addPerson = false;
                    }
                }
            }

            // Add the person if true
            if(addPerson){
                results.push_back(p[i]);
            }
        }
    }
    // If no match in search, add all.
    else if(results.size() == 0 && message == ""){
        results = p;
        message = "";
    }

    return results;
}

// Machine filter
vector<Machine> filterMachine(string &query, string &message){
    // No value command
    string noValCommand = getNoValueCommand(query);

    // Search
    vector<Machine> results = callSearchMachineDB(query, message, false);

    if(message != ""){
        return results;
    }

    // Everyone
    vector<Machine> m = callSearchMachineDB(noValCommand, message, true);

    if(message == ""){
        // Whether or not add the machine
        bool addMachine;

        for(unsigned int i = 0; i < m.size(); i++){
            addMachine = true;
            // Check search results
            if(results.size() != 0){
                for(unsigned int j = 0; j < results.size(); j++){
                    // Remove search match and do not add the machine
                    if(m[i] == results[j]){
                        results.erase(results.begin() + j);
                        addMachine = false;
                    }
                }
            }

            // Add the person if true
            if(addMachine){
                results.push_back(m[i]);
            }
        }
    }
    // If no match in search, add all.
    else if(results.size() == 0 && message == ""){
        results = m;
        message = "";
    }

    return results;
}

// Person machine filter
vector<PersonMachine> filterPM(string &query, string &message){
    // No value command
    string noValCommand = getNoValueCommand(query);

    // Search
    vector<PersonMachine> results = callSearchPMDB(query, message, false);

    if(message != ""){
        return results;
    }

    // Everyone
    vector<PersonMachine> pm = callSearchPMDB(noValCommand, message, true);

    if(message == ""){
        // Whether or not add the person-machine
        bool addPM;

        for(unsigned int i = 0; i < pm.size(); i++){
            addPM = true;
            // Check search results
            if(results.size() != 0){
                for(unsigned int j = 0; j < results.size(); j++){
                    // Remove search match and do not add the person machine
                    if(pm[i] == results[j]){
                        results.erase(results.begin() + j);
                        addPM = false;
                    }
                }
            }

            // Add the person if true
            if(addPM){
                results.push_back(pm[i]);
            }
        }
    }
    // If no match in search, add all.
    else if(results.size() == 0 && message == ""){
        results = pm;
        message = "";
    }

    return results;
}

// ===== ADD =====
// Person add
string addPerson(vector<Person> &p, const string &name, const string &gender, const string &dob, const string &dod, const string &country) {
    // Add to database
    addPersonDB(name, gender, dob, dod, country);

    // Re-populate vector
    populatePersonVector(p, ' ', false);

    return "Person " + name + " succesfully added.";
}

// Machine add
string addMachine(vector<Machine> &m, const string &name, const string &year, const string &built, const string &type, const string &system) {
    // Add to database
    addMachineDB(name, year, built, type, system);

    // Re-populate vector
    populateMachineVector(m, ' ', false);

    return "Machine " + name + " succesfully added.";
}

// ===== DELETE =====
string delPerson(vector<Person> &p, string &command){
    string name, message = ""; // Return message
    int id; // The extracted ID

    // Check for missing ID
    if(command.length() < 10){
        message = "ID is missing";
        return message;
    }

    // Remove "delete -p"
    command = command.erase(0,10);

    // Confirm the ID is a number
    if(!isNumber(command)){
        message = "ID must only contain digits";
        return message;
    }

    // Convert to int
    id = stoi(command);

    // Get index
    int index = getPIndexByID(p, id);

    // Get name
    name = p[index].getName();

    // Delete
    message = delPersonDB(id);

    // Success message
    if(message == ""){
        message = "| " + to_string(id) + " - " + name + " has been deleted.";
        populatePersonVector(p, ' ', false);
    }
    
    return message;
}

// Machine
string delMachine(vector<Machine> &m, string &command){
    string name, message = ""; // Return message
    int id; // The extracted ID

    // Check for missing ID
    if(command.length() < 10){
        message = "ID is missing";
        return message;
    }

    // Remove "delete -p"
    command = command.erase(0,10);

    // Confirm the ID is a number
    if(!isNumber(command)){
        message = "ID must only contain digits";
        return message;
    }

    // Convert to int
    id = stoi(command);

    // Get index
    int index = getMIndexByID(m, id);

    // Get name
    name = m[index].getName();

    // Delete
    message = delMachineDB(id);

    // Success message
    if(message == ""){
        message = "| " + to_string(id) + " - " + name + " has been deleted.";
        populateMachineVector(m, ' ', false);
    }
    return message;
}


// Person Machine
string delPM(vector<PersonMachine> &pm, string &command){
    string message = ""; // Return message
    int id; // The extracted ID

    // Check for missing ID
    if(command.length() < 11){
        message = "ID is missing";
        return message;
    }
    // Remove "delete -pm "
    command = command.erase(0,11);

    // Confirm the ID is a number
    if(!isNumber(command)){
        message = "ID must only contain digits";
        return message;
    }

    // Convert to int
    id = stoi(command);

    // Delete
    message = delPersMachDB(id);

    // Success message
    if(message == ""){
        message = "| Connection with ID: " + to_string(id) + " has been deleted.";
        populatePMVector(pm, ' ', false);
    }
    return message;
}

// ===== EDIT =====
// Person edit
string editPerson(vector<Person> &p, string command){
    string message = ""; // Return message
    string field = ""; // What field to edit
    int id = 0; // ID of person to edit
    string newValue = ""; // New value

    // Erase "edit -p "
    command = command.erase(0,8);

    // Split the command by whitespace
    vector<string> split = splitString(command, " ");

    if(split.size() < 3){
        message = "Too few arguments";
        return message;
    }

    // Extract field
    field = convert2Field(split[0], "person");

    // Verify field
    if(field == "id"){
        message = "ID cannot be edited";
        return message;
    }
    else if(field == "" || field == "-1"){
        message = "Unknown field specified: " + split[0];
        return message;
    }

    // Remove field from split
    split.erase(split.begin() + 0);

    // Extract ID
    string strID = split[0]; // The ID, string.

    // Verify ID
    if(!isNumber(strID)){
        message = "ID must be a positive integer";
        return message;
    }

    // Convert string ID to int ID
    id = stoi(strID);

    // Get index of element with corresponding ID
    int index = getPIndexByID(p, id);
    // If ID isn't in the database
    if(index == -1){
        message = "ID not found";
        return message;
    }

    // Remove id from split
    split.erase(split.begin() + 0);

    // Assemble what is left of split vector into a string
    newValue = assembleString(split, " ");

    // Error check
    if(newValue == ""){
        message = "New value not specified";
        return message;
    }
    // Gender
    else if(field == "gender"){
        if(newValue != "male" && newValue != "female"){
            if(newValue == "f"){
                newValue = "female";
            }
            else if(newValue == "m"){
                newValue = "male";
            }
            else{
                message = "Gender can only be male or female (m/f)";
                return message;
            }
        }
    }
    // Dates
    else if(field == "date_of_birth" || field == "date_of_death"){
        if(!verifyDate(newValue)){
            message = "Invalid date format";
            return message;
        }
    }

    // Get name of person being edited
    string name = p[index].getName();

    // Set new name
    message = editPersonDB(id, field, newValue);

    // SQL Error check
    if(message == ""){
        // Capital first letter
        field[0] = toupper(field[0]);

        // Confirmation message
        message = "ID " + strID + " - " + field + " of " + name + " changed to: " + newValue;
        populatePersonVector(p, ' ', false);
    }
    else{
        return message;
    }

    return message;
}

// Machine edit
string editMachine(vector<Machine> &m, string command){
    string message = ""; // Return message
    string table = ""; // What table to edit
    string field = ""; // What field to edit
    int id = 0; // ID of person to edit
    string newValue = ""; // New value

    // Split the command by whitespace
    vector<string> split = splitString(command, " ");

    if(split.size() < 5){
        message = "Too few arguments";
        return message;
    }

    // Remove "edit" from vector
    split.erase(split.begin() + 0);

    // Extract table
    table = split[0];
    split.erase(split.begin() + 0);

    // Extract field
    field = convert2Field(split[0], "machine");
    split.erase(split.begin() + 0);

    // Verify field
    if(field == "-i"){
        message = "ID cannot be edited";
        return message;
    }
    else if(field == "" || field == "-1"){
        message = "Unknown field specified";
        return message;
    }

    // Extract ID
    string strID = split[0]; // The ID, string.
    split.erase(split.begin() + 0);

    // Verify ID
    if(!isNumber(strID)){
        message = "ID must be a positive integer";
        return message;
    }

    // Convert string ID to int ID
    id = stoi(strID);

    // Get index of element with corresponding ID
    int index = getMIndexByID(m, id);
    // If ID isn't in the database
    if(index == -1){
        message = "ID not found";
        return message;
    }

    // Assemble what is left of split vector into a string
    newValue = assembleString(split, " ");

    // Error check
    // Value
    if(newValue == ""){
        message = "New value not specified";
        return message;
    }
    // Year
    else if(field == "year" && !isNumber(newValue)){
        message = "Year must be all digits";
        return message;
    }
    // Built
    else if(field == "built"){
        if(newValue != "y" && newValue != "yes" && newValue != "n" && newValue != "no"){
            message = "Built must be either yes or no (y/n)";
            return message;
        }
        else{
            newValue = stringBool(newValue);
        }
    }
    // Type
    else if(field == "type"){
        if(!isNumber(newValue)){
            message = "Type ID must be a positive number";
            return message;
        }

        bool exists = TSExistsDB(stoi(newValue), "mtype", message);

        if(message == ""){
            if(!exists){
                message = "The ID of specified type does not exist";
                return message;
            }
        }
        else{
            return message;
        }

        field = "mtype_id";
    }
    // Number System
    else if(field == "system"){
        if(!isNumber(newValue)){
            message = "Number system ID must be a positive number";
            return message;
        }

        bool exists = TSExistsDB(stoi(newValue), "num_sys", message);

        if(message == ""){
            if(!exists){
                message = "The ID of specified number system does not exist";
                return message;
            }
        }
        else{
            return message;
        }

        field = "num_sys_id";
    }

    // Get name of machine being edited
    string name = m[index].getName();

    // Set new name
    message = editMachineDB(id, field, newValue);

    // SQL Error check
    if(message == ""){
        // Capital first letter
        field[0] = toupper(field[0]);

        // Confirmation message
        message = "ID " + strID + " - " + field + " of " + name + " changed to: " + newValue;
        populateMachineVector(m, ' ', false);
    }
    else{
        return message;
    }

    return message;
}

// ===== CONNECT =====
// Connect person and machine
string conPM(const vector<Person> &p, const vector<Machine> &m, const string &command){
    vector<string> split = splitString(command, " ");

    // Check number of arguments
    if(split.size() != 3){
        return "Too few arguments. See help for instructions.";
    }
    // Verify person ID is a number
    else if(!isNumber(split[1])){
        return "Person ID must be a number";
    }
    // Verify machine ID is a number
    else if(!isNumber(split[2])){
        return "Machine ID must be a number";
    }

    // Convert to int
    int pid = stoi(split[1]);
    int mid = stoi(split[2]);

    // Add
    string message = addPersonMachineDB(pid, mid);

    // Get indexes
    int pindex = getPIndexByID(p, pid);
    int mindex = getMIndexByID(m, mid);

    // If error
    if(message != ""){

        if(message == "exists"){
            return "| A connection between " + p[pindex].getName() + " and " + m[mindex].getName() + " already exists";
        }

        return message;
    }

    return "| " + p[pindex].getName() + " and " + m[mindex].getName() + " successfully connected";
}
