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

// ===== SEARCH =====
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
string addPerson(vector<Person> &p, const string &name, const string &gender, const string &dob, const string &dod, const string &country) {
    // Add to database
    addPersonDB(name, gender, dob, dod, country);

    // Re-populate vector
    populatePersonVector(p, "");

    return "Person " + name + " succesfully added.";
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
string edit(vector<Person> &p, string command){
    string message = ""; // Return message
    string field = ""; // What field to edit
    int id = 0; // ID of person to edit
    string newValue = ""; // New value

    // Error check
    if(command.length() < 8){
        message = "Missing field and/or ID";
        return message;
    }

    // Remove "edit " from string
    command = command.erase(0,5);

    // Extract field
    field = command.substr(0,2);
    command = command.erase(0,3);

    // Extract ID
    int space = command.find(" "); // Next whitespace position
    string strID = command.substr(0,space); // The ID, string.
    command = command.erase(0,space + 1); // Erase ID

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

    // What is left of command is the new value
    newValue = command;
    // If value is missing
    if(newValue == ""){
        message = "New value not specified";
        return message;
    }

    string name = p[index].getName();
    field = convert2Field(field);

    if(field == "" || field == "-1"){
        message = "Unknown field specified";
        return message;
    }

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
    /*
    // Name
    if(field == "-n"){
        // Set new name
        message = editPersonDB(id, "name", newValue);

        // SQL Error check
        if(message == ""){
            // Confirmation message
            message = "ID " + strID + " - Name of " + name + " changed to: " + newValue;
            populatePersonVector(p, "");
        }
        else{
            return message;
        }
    }
    // Gender
    else if(field == "-g"){

        // Lowercase
        for(size_t i = 0; i < newValue.length(); i++){
            newValue[i] = tolower(newValue[i]);
        }

        // Male
        if(newValue == "m" || newValue == "male"){
            newValue = "male";
        }
        // Female
        else if(newValue == "f" || newValue == "female"){
            newValue = "female";
        }
        // Invalid
        else{
            message = "Invalid gender";
            return message;
        }

        // Set new gender
        message = editPersonDB(id, "gender", newValue);

        // SQL Error check
        if(message == ""){
            // Confirmation message
            message = "ID " + strID + " - Gender of " + name + " changed to: " + newValue;
            populatePersonVector(p, "");
        }
        else{
            return message;
        }
    }
    // Date of birth
    else if(field == "-b"){
            // Verify date
            if(!verifyDate(newValue)){
                message = "Incorrect date format";
                return message;
            }

            // Set new date of birth
            message = editPersonDB(id, "date_of_birth", newValue);

            // SQL Error check
            if(message == ""){
                // Confirmation message
                message = "ID " + strID + " - Birth date of " + name + " changed to: " + newValue;
                populatePersonVector(p, "");
            }
            else{
                return message;
            }
    }
    // Date of death
    else if(field == "-d"){
            // Verify date
            if(!verifyDate(newValue)){
                message = "Incorrect date format";
                return message;
            }

            // Set new name
            message = editPersonDB(id, "date_of_death", newValue);

            // SQL Error check
            if(message == ""){
                // Confirmation message
                message = "ID " + strID + " - Death date of " + name + " changed to: " + newValue;
                populatePersonVector(p, "");
            }
            else{
                return message;
            }
    }
    // Country
    else if(field == "-c"){
        // Set new name
        message = editPersonDB(id, "country", newValue);

        // SQL Error check
        if(message == ""){
            // Confirmation message
            message = "ID " + strID + " - Country of " + name + " changed to: " + newValue;
            populatePersonVector(p, "");
        }
        else{
            return message;
        }
    }
    else{
        message = "Unknown field specified";
        return message;
    }

    */

    return message;
}
