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
bool sortAlphabeticallyA(Person p1, Person p2);
bool sortAlphabeticallyD(Person p1, Person p2);

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
        cin >> command;

        if(command == "sort" || command == "sort -a"){
            sort(people.begin(), people.end(), sortAlphabeticallyA);
            display(people);
        }
        else if(command == "sortd"){
            sort(people.begin(), people.end(), sortAlphabeticallyD);
            display(people);
        }

    }

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

bool sortAlphabeticallyA(Person p1, Person p2){
    string s1 = p1.getName();
    string s2 = p2.getName();

    for(int i = 0; i < s1.length(); i++){
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) < toupper(s2[i]);
        }
    }
}

bool sortAlphabeticallyD(Person p1, Person p2){
    string s1 = p1.getName();
    string s2 = p2.getName();

    for(int i = 0; i < s1.length(); i++){
        if(toupper(s1[i]) != toupper(s2[i])){
            return toupper(s1[i]) > toupper(s2[i]);
        }
    }
}

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

