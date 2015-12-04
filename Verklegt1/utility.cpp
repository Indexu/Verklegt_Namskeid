#include "utility.h"

using namespace std;

// = UTILITY FUNCTIONS =

// Find the longest person name
int findLongestPName(const vector<Person> &p) {
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

// Find the longest machine name
int findLongestMName(const vector<Machine> &m) {
    int currentName, nameLength = 0;
    // Loop over vector
    for(unsigned int i = 0; i < m.size(); i++){
        // Current name length
        currentName = m[i].getName().length();
        // If it's longer than the longest name so far
        if (nameLength < currentName) {
            // New longest name
            nameLength = currentName;
        }
    }

    return nameLength;
}

// Find the longest machine type
int findLongestMType(const vector<Machine> &m) {
    int currentType, typeLength = 0;
    // Loop over vector
    for(unsigned int i = 0; i < m.size(); i++){
        // Current type length
        currentType = m[i].getType().length();
        // If it's longer than the longest type so far
        if (typeLength < currentType) {
            // New longest type
            typeLength = currentType;
        }
    }

    return typeLength;
}

// Verify date
bool verifyDate(const string &ver) {
    regex expr ("^[0-9]{2}/[0-9]{2}/[0-9]{4}$");
    if (regex_match(ver, expr)) {
       return true;
    }
    return false;
}

// Largest size_t value
size_t largestValue(const std::vector<size_t> &v){
    size_t largest = 0;

    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i] > largest){
            largest = v[i];
        }
    }

    return largest;
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

// Get person index by ID
int getPIndexByID(vector<Person> p, int id){
    int start = 0;
    int end = p.size() - 1;
    int middle = -1;
    int currentID;

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

// Get machine index by ID
int getMIndexByID(vector<Machine> m, int id){
    int start = 0;
    int end = m.size() - 1;
    int middle = -1;
    int currentID;

    while(start <= end){
        // Get middle element index
        middle = start + ((end - start)/2);

        // Get middle element's ID
        currentID = m[middle].getId();

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
// Convert arguments to field names
string convert2Field(string searchString, string database){
    string field;
    if (searchString == "-g"){
        field = "gender";
    }
    else if (searchString == "-c"){
        field = "country";
    }
    else if (searchString == "-n"){
        field = "name";
    }
    else if (searchString == "-b"){
        (database == "machine") ? field = "built" : field = "date_of_birth";
    }
    else if (searchString == "-d"){
        field = "date_of_death";
    }
    else if (searchString == "-i"){
        field = "id";
    }
    else if (searchString == "-y"){
        field = "year";
    }
    else if (searchString == "-t"){
        field = "mtype_id";
    }
    else if (searchString == "-s"){
        field = "num_sys_id";
    }

    else if(searchString == ""){
        field = "";
    }
    else {
        field = "-1";
    }
    return field;
}

