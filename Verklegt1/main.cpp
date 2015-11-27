#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include "person.h"

using namespace std;

// Print data
void display(vector<Person> p);
// Add data to vector
void populateVector(vector<Person> &p);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // The vector
    vector<Person> people;

    // Add data
    populateVector(people);

    // Print
    display(people);

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

