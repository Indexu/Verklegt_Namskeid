#include "utility.h"

using namespace std;

// = UTILITY FUNCTIONS =

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

// Get index by ID
int getIndexByID(vector<Person> p, int id){
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
