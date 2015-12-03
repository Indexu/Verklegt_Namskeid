#include "domain.h"
#include "data.h"
#include "person.h"
#include "utility.h"
#include <vector>
#include <regex>

using namespace std;

string startDB(){
    return initDB();
}

// ===== POPULATE VECTOR =====
string populateVector(vector<Person> &p){
    return getData(p);
}

// ===== SORTING =====
void sortNames(vector<Person> &p, const string &command){
    // Ascending - name
    if(command == "sort" || command == "sort -a"){
        sort(p.begin(), p.end(), sortNameAscend);
    }
    // Ascending - id
    else if (command == "sort -i") {
        sort(p.begin(), p.end(), sortByIdAscend);
    }
    // Descending - name
    else if(command == "sort -d"){
        sort(p.begin(), p.end(), sortNameDescend);
    }
    // Descending - id
    else if (command == "sort -iD") {
        sort(p.begin(), p.end(), sortByIdDescend);
    }
}

// Alphabetically name ascending
bool sortNameAscend(const Person p1, const Person p2){
    // Get names
    string s1 = p1.getName();
    string s2 = p2.getName();

    // Same name -> sort by ID
    if(s1 == s2){
        return sortByIdAscend(p1, p2);
    }

    // Loop over names
    for(unsigned int i = 0; i < s1.length(); i++){
        // Until letters are not the same
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) < toupper(s2[i]);
        }
    }

    return false;
}
// Alphabetically name descending
bool sortNameDescend(const Person p1, const Person p2){
    // Get names
    string s1 = p1.getName();
    string s2 = p2.getName();

    // Same name -> sort by ID
    if(s1 == s2){
        return sortByIdDescend(p1, p2);
    }

    // Loop over names
    for(unsigned int i = 0; i < s1.length(); i++){
        // Until letters are not the same
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) > toupper(s2[i]);
        }
    }

    return false;
}

// Sort table by ID
bool sortByIdAscend(const Person p1, const Person p2) {
    return (p1.getId() < p2.getId());
}
// Sort table by ID descending order
bool sortByIdDescend(const Person p1, const Person p2) {
    return (p1.getId() > p2.getId());
}

// ===== SEARCH =====
vector<Person> search(const vector<Person> &p, string &query, string &message){
    vector<Person> results; // Result vector
    vector<size_t> args; // Arguements
    message = "";

    // Check arguements
    args.push_back(query.find(" -C ")); // 0. Case-sensative
    args.push_back(query.find(" -a ")); // 1. Sort ascending
    args.push_back(query.find(" -z ")); // 2. Sort descending
    args.push_back(query.find(" -n ")); // 3. Name
    args.push_back(query.find(" -g ")); // 4. Gender
    args.push_back(query.find(" -b ")); // 5. Date of birth
    args.push_back(query.find(" -d ")); // 6. Date of death
    args.push_back(query.find(" -c ")); // 7. Country
    args.push_back(query.find(" -i ")); // 8. ID

    // Error check
    if(args[1] != string::npos && args[2] != string::npos){
        message = "Only one sorting method allowed!";
        return results;
    }

    // Extract search query
    int max = largestValue(args);
    // Erase up to query
    if(max != 0){
        query = query.erase(0, max + 4);
    }
    // No args
    else{
        query = query.erase(0,7);
    }

    // = Conduct search =

    // Gender
    if(query == "male" || query == "female"){
        for(unsigned int i = 0; i < p.size(); i++){
            if(p[i].getGender() == query){
                results.push_back(p[i]);
            }
        }
    }
    // Not Gender
    else{
        // Case sensetive
        if(args[0] != string::npos){
            bool valid;

            for(unsigned int i = 0; i < p.size(); i++){
                valid = false;

                // Name
                if(args[3] != string::npos){
                    if(p[i].getName().find(query) != string::npos){
                        valid = true;
                    }
                }
                // Date of birth
                else if(args[5] != string::npos){
                    if(p[i].getDateOfBirth().find(query) != string::npos){
                        valid = true;
                    }
                }
                // Date of death
                else if(args[6] != string::npos){
                    if(p[i].getDateOfDeath().find(query) != string::npos){
                        valid = true;
                    }
                }
                // Country
                else if(args[7] != string::npos){
                    if(p[i].getCountry().find(query) != string::npos){
                        valid = true;
                    }
                }
                // ID
                else if(args[8] != string::npos){
                    if(to_string(p[i].getId()).find(query) != string::npos){
                        valid = true;
                    }
                }
                // All fields
                else{
                    if(p[i].getName().find(query) != string::npos){
                        valid = true;
                    }
                    else if(p[i].getDateOfBirth().find(query) != string::npos){
                        valid = true;
                    }
                    else if(p[i].getDateOfDeath().find(query) != string::npos){
                        valid = true;
                    }
                    else if(p[i].getCountry().find(query) != string::npos){
                        valid = true;
                    }
                    else if(to_string(p[i].getId()).find(query) != string::npos){
                        valid = true;
                    }
                }
                // Check
                if(valid){
                    // Add
                    results.push_back(p[i]);
                }
            }
        }
        // Case insensetive
        else{

            for(unsigned int i = 0; i < query.length(); i++){
                query[i] = tolower(query[i]);
            }

            string temp;
            bool valid;
            for(unsigned int i = 0; i < p.size(); i++){
                valid = false;

                // Name
                if(args[3] != string::npos){
                    temp = p[i].getName();

                    for(unsigned int i = 0; i < temp.length(); i++){
                        temp[i] = tolower(temp[i]);
                    }

                    if(temp.find(query) != string::npos){
                        valid = true;
                    }
                }
                // Date of birth
                else if(args[5] != string::npos){
                    if(p[i].getDateOfBirth().find(query) != string::npos){
                        valid = true;
                    }
                }
                // Date of death
                else if(args[6] != string::npos){
                    if(p[i].getDateOfDeath().find(query) != string::npos){
                        valid = true;
                    }
                }
                // Country
                else if(args[7] != string::npos){
                    temp = p[i].getCountry();

                    for(unsigned int i = 0; i < temp.length(); i++){
                        temp[i] = tolower(temp[i]);
                    }

                    if(temp.find(query) != string::npos){
                        valid = true;
                    }
                }
                // ID
                else if(args[8] != string::npos){
                    if(to_string(p[i].getId()).find(query) != string::npos){
                        valid = true;
                    }
                }
                // All fields
                else{
                    // Name
                    temp = p[i].getName();

                    for(unsigned int i = 0; i < temp.length(); i++){
                        temp[i] = tolower(temp[i]);
                    }

                    if(temp.find(query) != string::npos){
                        valid = true;
                    }

                    // Date of birth
                    else if(p[i].getDateOfBirth().find(query) != string::npos){
                        valid = true;
                    }
                    // Date of death
                    else if(p[i].getDateOfDeath().find(query) != string::npos){
                        valid = true;
                    }
                    // ID
                    else if(to_string(p[i].getId()).find(query) != string::npos){
                        valid = true;
                    }
                    // Country
                    else{
                        temp = p[i].getCountry();

                        for(unsigned int i = 0; i < temp.length(); i++){
                            temp[i] = tolower(temp[i]);
                        }

                        if(temp.find(query) != string::npos){
                            valid = true;
                        }
                    }

                }
                // Check
                if(valid){
                    // Add
                    results.push_back(p[i]);
                }
            }
        }
    }

    // Sort ascending
    if(args[1] != string::npos){
        sort(results.begin(), results.end(), sortNameAscend);
    }
    // Sort descending
    else if(args[2] != string::npos){
        sort(results.begin(), results.end(), sortNameDescend);
    }

    if(results.size() == 0){
        message = "No results for query: \"" + query + "\"";
    }

    return results;
}

// ===== Filter =====
vector<Person> filter(const vector<Person> &p, string &query, string &message){
    // Search
    vector<Person> results = search(p, query, message);

    // If successful search
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
    populateVector(p);

    return "Person " + name + " succesfully added.";
}

// ===== DELETE =====
string del(vector<Person> &p, string &command){
    string name, message = ""; // Return message
    int id; // The extracted ID

    // Check for missing ID
    if(command.length() < 7){
        message = "ID is missing";
        return message;
    }

    // Remove "delete "
    command = command.erase(0,7);

    // Confirm the ID is a number
    if(!isNumber(command)){
        message = "ID must only contain digits";
        return message;
    }

    // Convert to int
    id = stoi(command);

    message = delPersonDB(id);

    // Success message
    if(message == ""){
        message = "| " + to_string(id) + " - " + name + " has been deleted.";
        populateVector(p);
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
    int index = getIndexByID(p, id); // The index of specified ID
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
    // Name
    if(field == "-n"){
        // Set new name
        message = editPersonDB(id, "name", newValue);

        // SQL Error check
        if(message == ""){
            // Confirmation message
            message = "ID " + strID + " - Name of " + name + " changed to: " + newValue;
            populateVector(p);
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
            populateVector(p);
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
                populateVector(p);
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
                populateVector(p);
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
            populateVector(p);
        }
        else{
            return message;
        }
    }
    else{
        message = "Unknown field specified";
        return message;
    }

    return message;
}
