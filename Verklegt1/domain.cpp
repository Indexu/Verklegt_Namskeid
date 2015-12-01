#include "domain.h"
#include "data.h"
#include "person.h"
#include <vector>
#include <regex>

using namespace std;

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
    vector<int> args; // Arguements
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
string add(vector<Person> &p, int &currentId, string name, string gender, string dob, string dod, string country) {
    // Add to person to vector
    Person temp(++currentId, name, gender, dob, dod, country);
    p.push_back(temp);
    setData(p);

    return "Person " + name + " succesfully added.";
}

// ===== DELETE =====
string del(vector<Person> &p, string &command){
    string name, message = ""; // Return message
    bool deleted = false; // If deleted
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

    // Loop over the vector and delete
    for(unsigned int i = 0; i < p.size(); i++){
        // Match
        if(p[i].getId() == id){
            name = p[i].getName(); // Store name
            p.erase(p.begin() + i); // Remove from vector
            deleted = true; // Confirm deleted
        }
    }

    // Success message
    if(deleted){
        message = "| " + to_string(id) + " - " + name + " has been deleted.";
        writeVector(p);
    }
    // ID not found message
    else{
        message = "ID: " + to_string(id) + " not found.";
    }

    // Return
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
        p[index].setName(newValue); // Set new name
        // Confirmation message
        message = "ID " + strID + " - Name of " + name + " changed to: " + newValue;
    }
    // Gender
    else if(field == "-g"){

        // Lowercase
        for(int i = 0; i < newValue.length(); i++){
            newValue[i] = tolower(newValue[i]);
        }

        // Male
        if(newValue == "m" || newValue == "male"){
            p[index].setGender("male");
            newValue = "male";
        }
        // Female
        else if(newValue == "f" || newValue == "female"){
            p[index].setGender("female");
            newValue = "female";
        }
        // Invalid
        else{
            message = "Invalid gender";
            return message;
        }

        // Confirmation message
        message = "ID " + strID + " - Gender of " + name + " changed to: " + newValue;
    }
    // Date of birth
    else if(field == "-b"){
            // Verify date
            if(!verifyDate(newValue)){
                message = "Incorrect date format";
                return message;
            }

            p[index].setDateOfBirth(newValue); // Set new date of birth
            // Confirmation message
            message = "ID " + strID + " - Birth date of " + name + " changed to: " + newValue;
    }
    // Date of death
    else if(field == "-d"){
            // Verify date
            if(!verifyDate(newValue)){
                message = "Incorrect date format";
                return message;
            }

            p[index].setDateOfDeath(newValue); // Set new date of death
            // Confirmation message
            message = "ID " + strID + " - Death date of " + name + " changed to: " + newValue;
    }
    // Country
    else if(field == "-c"){
        p[index].setCountry(newValue); // Set new country
        // Confirmation message
        message = "ID " + strID + " - Country of " + name + " changed to: " + newValue;
    }
    else{
        message = "Unknown field specified";
        return message;
    }

    return message;
}

// ===== OTHER =====

// Find the longest name
int findLongestName(const vector<Person> &p) {
    int currentName, nameLength = 0;
    // Loop over vector
    for(unsigned int i = 0; i < p.size(); i++){
        // Current name length
        currentName = p[i].getName().length();
        // If it's longer than the longest name so far
        if (nameLength < currentName) {
            // New longest name
            nameLength = currentName;
        }
    }

    return nameLength;
}

// Verify date
bool verifyDate(const string &ver) {
    regex expr ("^[0-9]{2}/[0-9]{2}/[0-9]{4}$");
    if (regex_match(ver, expr)) {
       return true;
    }
    return false;
}

// Largest int value
int largestValue(const vector<int> &v){
    int largest = 0;

    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i] > largest){
            largest = v[i];
        }
    }

    return largest;
}

//Add vector to text file
void writeVector(const vector<Person> &p){
    setData(p);

}

// Populate vector
void populateVector(vector<Person> &p, string &message){
    getData(p, message);
}

// Get the command
string getCommand(const string &command) {
    int findSpace = command.find(" ");
    return command.substr(0,findSpace);
}

// Get current id
int getCurrentId(const vector<Person> &p) {
    int currentId, largestId = 0;
    // Loop over vector
    for(unsigned int i = 0; i < p.size(); i++){
        // Current id
        currentId = p[i].getId();
        // If it's longer than the largest id so far
        if (largestId < currentId) {
            // New largest id
            largestId = currentId;
        }
    }

    return largestId;
}

// Verify string as number
bool isNumber(const string &str){
    for(unsigned int i = 0; i < str.length(); i++){
        if(!isdigit(str[i])){
            return false;
        }
    }

    return true;
}

// Get index by ID
int getIndexByID(vector<Person> p, int id){
    bool found = false;
    int start = 0;
    int end = p.size() - 1;
    int middle = -1;
    int currentID;

    // Sort by ID
    sort(p.begin(), p.end(), sortByIdAscend);

    while(start <= end){
        // Get middle element index
        middle = start + ((end - start)/2);

        // Get middle element's ID
        currentID = p[middle].getId();

        // Found
        if(currentID == id){
            return middle;
        }
        // Higher
        else if(currentID < id){
            start = middle + 1;
        }
        // Lower
        else{
            end = middle - 1;
        }
    }

    // Not found
    if(end < start){
        middle = -1;
    }

    return middle;
}

// Verify gender input
string verifyGender(string g){
    g = tolower(g[0]);

    if(g == ""){
        g = "Please enter a gender.";
    }
    else if(g[0] != 'm' && g[0] != 'f'){
        g = "Invalid gender input";
    }
    else{
        g = (g[0] == 'm') ? g = "male" : g = "female";
    }

    return g;
}
