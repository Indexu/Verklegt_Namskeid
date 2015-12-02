#include "data.h"
#include <fstream>
#include <sstream>

using namespace std;

// Get data
void getData(vector<Person> &p, string &message){
    // Load file
    ifstream ifile("people.txt");
    // Check file and continue
    if(!ifile.is_open()) {
        message = "Unable to open file...";
        return;
    }

    // Vars
    string line, id, name, gender, dob, dod, country;
    while (getline(ifile, line)) {
        istringstream tokens(line);
        getline(tokens, id, ',');
        getline(tokens, name, ',');
        getline(tokens, gender, ',');
        getline(tokens, dob, ',');
        getline(tokens, dod, ',');
        getline(tokens, country, ',');

        // Create person
        Person temp(stoi(id), name, gender, dob, dod, country);
        // Add to person to vector
        p.push_back(temp);
    }
    // Close
    ifile.close();
}

// Set data
void setData(const vector<Person> &p){
    ofstream outputFile;

    outputFile.open("people.txt");

    for(unsigned int i=0; i < p.size(); i++){
        outputFile << p[i].getId() << ",";
        outputFile << p[i].getName() << ",";
        outputFile << p[i].getGender() << ",";
        outputFile << p[i].getDateOfBirth() << ",";
        outputFile << p[i].getDateOfDeath() << ",";
        outputFile << p[i].getCountry() << endl;
    }

    outputFile.close();

}
