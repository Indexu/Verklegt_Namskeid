#include "domain.h"
#include "data.h"
#include "person.h"
#include "machine.h"
#include "utility.h"
#include <vector>
#include <regex>

using namespace std;

string startDB(){
    return initDB();
}

// ===== POPULATE PERSON VECTOR =====
string populatePersonVector(vector<Person> &p, const string &sorting){
    return getPersonsDB(p, sorting);
}

// ===== POPULATE MACHINE VECTOR =====
string populateMachineVector(vector<Machine> &m, const string &sorting){
    return getMachinesDB(m, sorting);
}

// ===== POPULATE TYPES AND SYSTEMS VECTOR =====
string populateTSVector(vector<TypeSystem> &ts, const string table, const string &sorting){
    return getTSDB(ts, table, sorting);
}

// ===== LIST =====
// Persons
vector<Person> listPersons(string &command, string &message){
    vector<Person> p;

    command = command.erase(0,6);

    if(command == "-a"){
        populatePersonVector(p, "a");
    }
    else if(command == "-z"){
        populatePersonVector(p, "z");
    }
    else if(command == "-d"){
        populatePersonVector(p, "d");
    }
    else if(command == ""){
        populatePersonVector(p, "");
    }
    else{
        message = "Invalid flag: \"" + command + "\"";
    }

    return p;
}

// Machines
vector<Machine> listMachines(string &command, string &message){
    vector<Machine> m;

    command = command.erase(0,6);

    if(command == "-a"){
        populateMachineVector(m, "a");
    }
    else if(command == "-z"){
        populateMachineVector(m, "z");
    }
    else if(command == "-d"){
        populateMachineVector(m, "d");
    }
    else if(command == ""){
        populateMachineVector(m, "");
    }
    else{
        message = "Invalid flag: \"" + command + "\"";
    }

    return m;
}

// Types and systems
vector<TypeSystem> listTS(string &command, string &message){
    vector<TypeSystem> ts;

    // Split
    vector<string> split = splitString(command, " ");
    // 0. ls
    // 1. table
    // 2. sort

    if(split[1] == "-t"){
        split[1] = "mtype";
    }
    else{
        split[1] = "num_sys";
    }

    if(split.size() == 2){
        populateTSVector(ts, split[1], "");
    }
    else if(split[2] == "-a"){
        populateTSVector(ts, split[1], "a");
    }
    else if(split[2] == "-z"){
        populateTSVector(ts, split[1], "z");
    }
    else if(split[2] == "-d"){
        populateTSVector(ts, split[1], "d");
    }
    else if(split[2] == ""){
        populateTSVector(ts, split[1], "");
    }
    else{
        message = "Invalid flag: \"" + split[2] + "\"";
    }

    return ts;
}

// ===== SEARCH =====
// Person search
vector<Person> callSearchPersonDB(string &query, string &message) {
    // Result vector
    vector<Person> results;
    // Reset message
    message = "";
    // Field flag
    string arg = "";

    // Erase command + -p/-m
    query.erase(0,10);

    // Get field flag
    if(query.substr(0,1) == "-"){
        arg = query.substr(0,2);
        query.erase(0,3);
    }

    string searchString = query;
    string field = convert2Field(arg, "person");

    results = searchPersonDB(searchString, message, field);

    if(message == ""){
        if (results.empty()) {
            message = "No entries matched your search.";
        }
    }
    return results;
}

// Machine search
vector<Machine> callSearchMachineDB(string &query, string &message) {
    // Result vector
    vector<Machine> results;
    // Reset message
    message = "";
    // Field flag
    string arg = "";

    // Erase command + -p/-m
    query.erase(0,10);

    // Get field flag
    if(query.substr(0,1) == "-"){
        arg = query.substr(0,2);
        query.erase(0,3);
    }

    string searchString = query;
    string field = convert2Field(arg, "machine");

    results = searchMachineDB(searchString, message, field);

    if(message == ""){
        if (results.empty()) {
            message = "No entries matched your search.";
        }
    }
    return results;
}

// ===== Filter =====
vector<Person> filter(string &query, string &message){
    // Everyone
    vector<Person> p;
    // Search
    vector<Person> results = callSearchPersonDB(query, message);

    // If successful search
    if(message == ""){
        // Get all persons
        message = populatePersonVector(p, "");

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
    }
    // If no match in search, add all.
    else if(results.size() == 0 && message[0] != 'O'){
        results = p;
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
    populatePersonVector(p, "");

    return "Person " + name + " succesfully added.";
}

// Machine add
string addMachine(vector<Machine> &m, const string &name, const string &year, const string &built, const string &type, const string &system) {
    // Add to database
    addMachineDB(name, year, built, type, system);

    // Re-populate vector
    populateMachineVector(m, "");

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
        populatePersonVector(p, "");
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
        populateMachineVector(m, "");
    }

    return message;
}


// ===== EDIT =====
// Person edit
string editPerson(vector<Person> &p, string command){
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
    field = convert2Field(split[0], "person");
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
    int index = getPIndexByID(p, id);
    // If ID isn't in the database
    if(index == -1){
        message = "ID not found";
        return message;
    }

    // Assemble what is left of split vector into a string
    newValue = assembleString(split, " ");

    // If value is missing
    if(newValue == ""){
        message = "New value not specified";
        return message;
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
        populatePersonVector(p, "");
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

    // If value is missing
    if(newValue == ""){
        message = "New value not specified";
        return message;
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
        populateMachineVector(m, "");
    }
    else{
        return message;
    }

    return message;
}
