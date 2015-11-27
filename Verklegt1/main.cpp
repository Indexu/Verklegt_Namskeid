#include <QCoreApplication>
#include <iostream>
#include <fstream>
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
// Search for name
void search(vector<Person> &p, string query, int longestName);
// Verify date input
bool verifyDate(string ver);
// Find longest name in database
int findLongestName(vector<Person> &p);
// Add new person to vector
void add(vector<Person> &p);

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

    longestName = findLongestName(people);

    // Print
    display(people, longestName);

    // ===== MAIN =====

    while(command != "q"){
        cout << ">";

        // Get command
        getline(cin, command);

        // Sort - Ascending
        if(command == "sort" || command == "sort -a"){
            sort(people.begin(), people.end(), sortNameAscend);
            display(people, longestName);
        }
        // Sort - Descending
        else if(command == "sort -d"){
            sort(people.begin(), people.end(), sortNameDescend);
            display(people, longestName);

        }
        else if(command.substr(0,6) == "search"){
            search(people, command, longestName);
        }
        else if(command == "add") {
            add(people);
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
    if(ifile.is_open()){
        // Vars
        string line, name, gender, dob, dod, country;
        int count;

        // Read file
        while(getline(ifile, line)){
            // Default values for each line
            count = 0;
            name = "";
            gender = "";
            dob = "";
            dod = "";
            country = "";

            // Loop over line
            for(unsigned int i = 0; i < line.length(); i++){
                // Seperate by comma
                if(line[i] == ','){
                    count++;
                    continue;
                }

                // Add to appropriate variable
                switch(count){
                    case 0:
                        name += line[i];
                        break;
                    case 1:
                        gender += line[i];
                        break;
                    case 2:
                        dob += line[i];
                        break;
                    case 3:
                        dod += line[i];
                        break;
                    case 4:
                        country += line[i];
                        break;
                }
            }
            // Create person
            Person temp(name, gender, dob, dod, country);
            // Add to person to vector
            p.push_back(temp);
        }
    }
}

// ===== SORTING =====
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

    // Case sensetive
    if(query.substr(7,2) == "-c"){
        query = query.erase(0,10);

        for(unsigned int i = 0; i < p.size(); i++){
            if(p[i].getName().find(query) != string::npos){
                results.push_back(p[i]);
            }
        }
    }
    // Case insensetive
    else{
        query = query.erase(0,7);

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

    display(results, longestName);
}

// ===== OTHER =====

// Display
void display(vector<Person> p, int longestName){
    cout << "| ";
    cout << setw(longestName) << "Name" << " | ";
    cout <<  setw(6) << "GENDER" << " | ";
    cout << setw(10) << "DOB" << " | ";
    cout << setw(10) << "DOD" << " | ";
    cout <<  setw(4) << "Country" << endl;
    // loops through vector
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].display(longestName);
    }
}

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

void add(vector<Person> &p) {
    string name, gender, dob, dod = "", country;
    cout << "Name: ";
    getline(cin, name);
    cout << "Gender (M/F): ";
    cin >> gender;
    cout << "Date of birth (DD/MM/YYYY): ";
    cin >> dob;
    cout << "Date of death (same form as above, if alive: -): ";
    cin >> dod;
    cout << "Country of origin: ";
    cin >> country;

    if (verifyDate(dob) && verifyDate(dod)) {
        if (tolower(gender[0]) == 'm' || tolower(gender[0]) == 'f') {
            gender = (gender[0] == 'm') ? gender = "male" : gender = "female";

            Person temp(name, gender, dob, dod, country);
            // Add to person to vector
            cout << "Person " << name << " succesfully added." << endl;
            p.push_back(temp);
        }
        else {
            cout << "Invalid gender input.";
        }
    }
    else {
        cout << "Invalid date format.";
    }
}

bool verifyDate(string ver) {
    regex expr ("^[0-9]{2}\/[0-9]{2}\/[0-9]{4}$");
    if (regex_match(ver, expr) || ver == "-") {
       return true;
    }
    return false;
}
