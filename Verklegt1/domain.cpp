#include "domain.h"
#include "data.h"
#include "person.h"
#include <vector>
#include <regex>

using namespace std;

// ===== SORTING =====
void sortNames(vector<Person> &p, const string &command){
    // Ascending
    if(command == "sort" || command == "sort -a"){
        sort(p.begin(), p.end(), sortNameAscend);
    }
    else if (command == "sort -i") {
        sort(p.begin(), p.end(), sortByIdAscend);
    }
    // Descending
    else if(command == "sort -d"){
        sort(p.begin(), p.end(), sortNameDescend);
    }
    else if (command == "sort -iD") {
        sort(p.begin(), p.end(), sortByIdDescend);
    }
}

// Alphabetically name ascending
bool sortNameAscend(const Person p1, const Person p2){
    // Get names
    string s1 = p1.getName();
    string s2 = p2.getName();

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
void add(vector<Person> &p, int &currentId) {
    // Vars
    string name, gender, dob, dod = "", country;
    bool valid;

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

       gender = tolower(gender[0]);

        if(gender == ""){
            cout << "Please enter a gender." << endl;
        }
        else if(gender[0] != 'm' && gender[0] != 'f'){
            cout << "Invalid gender input" << endl;
        }
        else{
            gender = (gender[0] == 'm') ? gender = "male" : gender = "female";
        }
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
        cout << "Date of death (DD/MM/YYYY, if alive: -): ";
        getline(cin, dod);

        if(dod == "-"){
            dod = "";
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

    // Add to person to vector
    Person temp(++currentId, name, gender, dob, dod, country);
    p.push_back(temp);
    setData(p);
    cout << "Person " << name << " succesfully added." << endl;
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

    for(int i = 0; i < v.size(); i++){
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
    for(int i = 0; i < str.length(); i++){
        if(!isdigit(str[i])){
            return false;
        }
    }

    return true;
}
