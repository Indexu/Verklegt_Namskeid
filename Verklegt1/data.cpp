#include "data.h"
#include <fstream>
#include <sstream>

using namespace std;

void getData(vector<Person> &p){
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
