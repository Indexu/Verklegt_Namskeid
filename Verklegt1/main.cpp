#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "person.h"
#include <iomanip>
#include <regex>

using namespace std;

// Print data
void display(vector<Person> p, int longestName);
// Add data to vector
void populateVector(vector<Person> &p);
// Sort vector
bool sortNameAscend(Person p1, Person p2);
bool sortNameDescend(Person p1, Person p2);
// Get the longest name in the vector
int findLongestName(vector<Person> &p);
// Sort names
void sortNames(vector<Person> &p, string command, int longestName);
// Search for name
void search(vector<Person> &p, string query, int longestName);
// Verify date input
bool verifyDate(string ver);
// Find longest name in database
int findLongestName(vector<Person> &p);
// Add new person to vector
void add(vector<Person> &p);
// Help dialog
void help();
//Add vector to text file
void addInfo(vector<Person> &p);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== SETUP =====

    // Vars
    string command = ""; // User command
    vector<Person> people; // The data vector
    int longestName; // Longest name var

    // Add data
    populateVector(people);

    // Get longest name
    longestName = findLongestName(people);

    // Print
    display(people, longestName);

    // ===== MAIN =====

    while(command != "q"){
        cout << ">";

        // Get command
        getline(cin, command);

        // Display the vector
        if(command == "display" || command == "list"){
            display(people, longestName);
        }
        // Sort
        else if(command.substr(0,4) == "sort"){
            sortNames(people, command, longestName);
        }
        // Search
        else if(command.substr(0,6) == "search"){
            search(people, command, longestName);
        }
        // Add
        else if(command == "add") {
            add(people);
            addInfo(people);
        }
        else if(command == "help"){
            help();
        }
        else if(command != ""){
            cout << "Invalid command." << endl;
        }
    }

    // ===== END =====
    return a.exec();
}

// Populate vector
void populateVector(vector<Person> &p){
    // Load file
    ifstream ifile("people.txt");
    // Check file and continue
    if(!ifile.is_open()) {
        cout << "Unable to open file..." << endl;
        return;
    }

    // Vars
    string line, name, gender, dob, dod, country;
    while (getline(ifile, line)) {
        istringstream tokens(line);
        getline(tokens, name, ',');
        getline(tokens, gender, ',');
        getline(tokens, dob, ',');
        getline(tokens, dod, ',');
        getline(tokens, country, ',');

        // Create person
        Person temp(name, gender, dob, dod, country);
        // Add to person to vector
        p.push_back(temp);
    }
    // Close
    ifile.close();
}

// ===== SORTING =====
void sortNames(vector<Person> &p, string command, int longestName){
    // Ascending
    if(command == "sort" || command == "sort -a"){
        sort(p.begin(), p.end(), sortNameAscend);
        display(p, longestName);
    }
    // Descending
    else if(command == "sort -d"){
        sort(p.begin(), p.end(), sortNameDescend);
        display(p, longestName);

    }
}

// Alphabetically name ascending
bool sortNameAscend(Person p1, Person p2){
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
bool sortNameDescend(Person p1, Person p2){
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

// ===== SEARCH =====
void search(vector<Person> &p, string query, int longestName){
    vector<Person> results;

    // Check arguements
    int caseSensetive = query.find(" -c ");
    int sorta = query.find(" -a ");
    int sortd = query.find(" -d ");

    // Error check
    if(sorta != string::npos && sortd != string::npos){
        cout << "Only one sorting method allowed!" << endl;
        return;
    }

    // Extract search query
    // -a last arguement
    if(caseSensetive < sorta){
        query = query.erase(0,sorta + 4);
    }
    // -d last arguement
    else if(caseSensetive < sortd){
        query = query.erase(0,sortd + 4);
    }
    // -c last arguement
    else if(caseSensetive != string::npos){
        query = query.erase(0,caseSensetive + 4);
    }
    // no arguement
    else{
        query = query.erase(0,7);
    }

    // Conduct search
    // Case sensetive
    if(caseSensetive != string::npos){

        for(unsigned int i = 0; i < p.size(); i++){
            if(p[i].getName().find(query) != string::npos){
                results.push_back(p[i]);
            }
        }
    }
    // Case insensetive
    else{

        for(unsigned int i = 0; i < query.length(); i++){
            query[i] = tolower(query[i]);
        }

        string name;
        for(unsigned int i = 0; i < p.size(); i++){
            name = p[i].getName();

            for(unsigned int i = 0; i < name.length(); i++){
                name[i] = tolower(name[i]);
            }

            if(name.find(query) != string::npos){
                results.push_back(p[i]);
            }
        }
    }

    // Sort ascending
    if(sorta != string::npos){
        sort(results.begin(), results.end(), sortNameAscend);
    }
    // Sort descending
    else if(sortd != string::npos){
        sort(results.begin(), results.end(), sortNameDescend);
    }

    // Display
    display(results, longestName);
}

// ===== ADD =====
void add(vector<Person> &p) {
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

        valid = verifyDate(dod);

        if(!valid){
            cout << "Invalid date format." << endl;
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
    Person temp(name, gender, dob, dod, country);
    p.push_back(temp);
    cout << "Person " << name << " succesfully added." << endl;
}

// ===== HELP =====
void help(){

}
//Add vector to text file
void addInfo(vector<Person> &p){
    ofstream outputFile;

        outputFile.open("people.txt");

        for(unsigned int i=0; i < p.size(); i++){
            outputFile << p[i].getName() << ",";
            outputFile << p[i].getGender() << ",";
            outputFile << p[i].getDateOfBirth() << ",";
            outputFile << p[i].getDateOfBirth() << ",";
            outputFile << p[i].getCountry() << endl;
        }

        outputFile.close();

}

// ===== OTHER =====

// Display
void display(vector<Person> p, int longestName){
    cout << "| ";
    cout << left << setw(longestName) << "Name" << " | ";
    cout << setw(6) << "Gender" << " | ";
    cout << setw(10) << "Birth date" << " | ";
    cout << setw(10) << "Death date" << " | ";
    cout << setw(4) << "Country" << endl;

    for(int i = 0; i < (47 + longestName); i++){
        cout << "-";
    }
    cout << endl;

    // loops through vector
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].display(longestName);
    }
}

// Find the longest name
int findLongestName(vector<Person>& p) {
    // Set first element to longest name
    int nameLength = p[0].getName().length();
    // Loop over vector
    for(unsigned int i = 1; i < p.size(); i++){
        if ((int)p[i].getName().length() > nameLength) {
            nameLength = p[i].getName().length();
        }
    }
    return nameLength;
}

// Verify date
bool verifyDate(string ver) {
    regex expr ("^[0-9]{2}\/[0-9]{2}\/[0-9]{4}$");
    if (regex_match(ver, expr) || ver == "-") {
       return true;
    }
    return false;
}
