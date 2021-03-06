#include "utility.h"

using namespace std;

// = UTILITY FUNCTIONS =

// Find the longest person name
int findLongestPName(const vector<Person> &p) {
    size_t currentName;
    size_t nameLength = 0;
    // Loop over vector
    for(unsigned int i = 0; i < p.size(); i++){
        // Current name length
        currentName = p[i].getName().length();
        // If it's longer than the longest name so far
        if (nameLength < currentName) {
            // New longest nam
            nameLength = currentName;
        }
    }

    return nameLength;
}

// Find the longest machine name
int findLongestMName(const vector<Machine> &m) {
    size_t currentName;
    size_t nameLength = 0;
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
    size_t currentType;
    size_t typeLength = 0;
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

// Find the longest typesystem name
int findLongestTSName(const vector<TypeSystem> &ts) {
    size_t currentName;
    size_t nameLength = 0;
    // Loop over vector
    for(unsigned int i = 0; i < ts.size(); i++){
        // Current name length
        currentName = ts[i].getName().length();
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
    regex expr ("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");

    // Check regex match
    if (regex_match(ver, expr)) {
        // Get month and day integers
       int month = stoi(ver.substr(5,2));
       int day = stoi(ver.substr(8,2));

       // Month between 1 and 12
       if(month > 12 || month < 1){
           return false;
       }
       // Day between 1 and 31
       else if(day > 31 || day < 1){
           return false;
       }
       else{
           return true;
       }
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
    size_t findSpace = command.find(" ");
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
    int end = (int)p.size() - 1;
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
    int end = (int)m.size() - 1;
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
    if (searchString == "-n"){
            field = "name";
    }
    else if (searchString == "-i"){
        field = "id";
    }
    else if(database == "machine"){
        if (searchString == "-b"){
            field = "built";
        }
        else if (searchString == "-y"){
            field = "year";
        }
        else if (searchString == "-t"){
            field = "type";
        }
        else if (searchString == "-s"){
            field = "system";
        }
        else if(searchString == ""){
            field = "";
        }
        else {
            field = "-1";
        }
    }
    else if(database == "PM") {
        if (searchString == "-p"){
            field = "p_name";
        }
        else if (searchString == "-m"){
            field = "m_name";
        }
        else if (searchString == "-t"){
            field = "m_type";
        }
        else if (searchString == "-s"){
            field = "m_system";
        }
        else if (searchString == "-c"){
            field = "p_country";
        }
        else if (searchString == ""){
            field = "";
        }
        else{
            field = "-1";
        }
    }
    else{
        if (searchString == "-g"){
            field = "gender";
        }
        else if (searchString == "-c"){
            field = "country";
        }
        else if (searchString == "-b"){
            field = "date_of_birth";
        }
        else if (searchString == "-d"){
            field = "date_of_death";
        }
        else if(searchString == "-e"){
            field = "date_of_death";
        }
        else if(searchString == ""){
            field = "";
        }
        else {
            field = "-1";
        }
    }
    return field;
}

// Split a string to vector
vector<string> splitString(string input, string delim){
    vector<string> split;
    // Position of delimiter
    size_t delimPos = input.find(delim);

    while (input != "" && delimPos != string::npos){
        // Get next pos
        delimPos = input.find(delim);

        // If found, add up to delimPos to vector and erase up to delimPos+1
        if (delimPos != string::npos){
            split.push_back(input.substr(0, delimPos));
            input = input.erase(0, delimPos+1);
        }
        // If not found, add what is left of input
        else{
            split.push_back(input);
        }
    }

    // If no delimiter was found in string, return it in vector
    if(split.empty()){
        split.push_back(input);
    }

    return split;
}

// Assemble a string from vector
string assembleString(vector<string> inputVect, string delim){
    string assembled = "";

    for (size_t i = 0; i < inputVect.size(); i++)
    {
        // Append vector element to string
        assembled += inputVect[i];

        // If not the last element, add the delimiter
        if (i + 1 < inputVect.size()){
            assembled += delim;
        }
    }

    return assembled;
}

// Convert 1's and 0's to yes and no
string boolYesNo(bool num) {
    string yesNo = "";
    (num) ? yesNo = "yes" : yesNo = "no";
    return yesNo;
}

// Yes no to bool
bool stringBool(string s){
    return (s == "y" || s == "yes") ? true : false;
}

// Get a vector of arguments from a string
vector<string> getArgs(string query) {
    vector<string> args = splitString(query, " ");
    vector<string> result;
    // Loop through the vector given by splitString and put arguments in results vector
    for (int i = 0; i < (int)args.size(); i++) {
        if (args[i].substr(0,1) == "-") {
            result.push_back(args[i]);
        }
        else {
            break;
        }
    }
    return result;
}

// Parse the search arguments
string parseSearchArgs(string &query, string &searchString, vector<string> &arguments, string &arg, string &sort, bool &desc, const string &db){
    // Set variables depending on the arguments
    if (arguments.size() == 0){
        searchString = query;
    }
    // Args = 1
    else if (arguments.size() == 1){
        // Sort
        if (arguments[0].length() == 3){
            sort = arguments[0].erase(1,1);
            query.erase(0,4);
        }
        // Descending
        else if(arguments[0] == "-d"){
            desc = true;
            query.erase(0,3);
        }
        // Field
        else if (arguments[0].length() == 2){
            arg = convert2Field(arguments[0], db);
            query.erase(0,3);
        }
    }
    // Args = 2
    else if (arguments.size() == 2){
        // Arg or sort
        if(arguments[0].length() == 2){
            arg = convert2Field(arguments[0], db);
            query.erase(0,3);
        }
        else{
            sort = arguments[0].erase(1,1);
            query.erase(0,4);
        }
        // Check for double sort
        if(sort != "" && arguments[1].length() == 3 && arguments[1].substr(0,2) == "-s"){
            return "Only one sorting method allowed";
        }
        // Sort or descend
        else if(arguments[1] != "-d"){
            sort = arguments[1].erase(1,1);
            query.erase(0,4);
        }
        else{
           desc = true;
           query.erase(0,3);
        }
    }
    // Args = 3
    else if (arguments.size() == 3){
        // Arg
        arg = convert2Field(arguments[0], db);
        // Sort
        sort = arguments[1].erase(1,1);

        // Descending
        if(arguments[2] != "-d"){
            return "Invalid flag: " + arguments[2];
        }
        else{
           desc = true;
        }

        query.erase(0,10);
    }
    // Args > 3
    else {
        return "Too many arguments.";
    }

    // What is left of query is the search string
    searchString = query;

    // Check for descending
    if (sort == "-d") {
        desc = true;
    }

    return "";
}

// Get a command without the value
string getNoValueCommand(string query){
    vector<string> split = splitString(query, " ");
    vector<string> result;

    // Add base command
    result.push_back(split[0]);

    // Loop through the vector given by splitString and put arguments in results vector
    for (int i = 1; i < (int)split.size(); i++) {
        if (split[i].substr(0,1) == "-") {
            result.push_back(split[i]);
        }
        else {
            break;
        }
    }
    return assembleString(result, " ");
}
