#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "person.h"

using namespace std;

// Print data
void display(vector<Person> p);
// Add data to vector
void populateVector(vector<Person> &p);
// Sort vector
bool sortNameAscend(Person p1, Person p2);
bool sortNameDescend(Person p1, Person p2);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== SETUP =====

    // Vars
    string command = "";
    vector<Person> people; // The data vector

    // Add data
    populateVector(people);

    // Print
    display(people);

    // ===== MAIN =====

    while(command != "q"){
        cout << ">";

        // Get command
        getline(cin, command);

        // Sort - Ascending
        if(command == "sort" || command == "sort -a"){
            sort(people.begin(), people.end(), sortNameAscend);
            display(people);
        }
        // Sort - Descending
        else if(command == "sortd" || command == "sort -d"){
            sort(people.begin(), people.end(), sortNameDescend);
            display(people);
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
            for(int i = 0; i < line.length(); i++){
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
    for(int i = 0; i < s1.length(); i++){
        // Until letters are not the same
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) < toupper(s2[i]);
        }
    }
}
// Alphabetically name descending
bool sortNameDescend(Person p1, Person p2){
    // Get names
    string s1 = p1.getName();
    string s2 = p2.getName();

    // Loop over names
    for(int i = 0; i < s1.length(); i++){
        // Until letters are not the same
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) > toupper(s2[i]);
        }
    }
}

// ===== OTHER =====

// Display
void display(vector<Person> p){
    // Loop over vector
    for(int i = 0; i < p.size(); i++){
        cout << p[i].getName() << " | ";
        cout << p[i].getGender() << " | ";
        cout << p[i].getDateOfBirth() << " | ";
        cout << p[i].getDateOfDeath() << " | ";
        cout << p[i].getCountry() << endl;
    }
}

