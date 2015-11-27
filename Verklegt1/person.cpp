#include "person.h"
#include <iomanip>
#include <iostream>
using namespace std;

// Constructor - With date of death
Person::Person(string n, string g, string dob, string dod, string c){
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = dod;
    Country = c;
}

// Get set name
string Person::getName(){
    return Name;
}
void Person::setName(std::string n){
    Name = n;
}

// Get set gender
string Person::getGender(){
    return Gender;
}
void Person::setGender(string g){
    Gender = g;
}

// Get set date of birth
string Person::getDateOfBirth(){
    return DateOfBirth;
}
void Person::setDateOfBirth(string dob){
    DateOfBirth = dob;
}

// Get set date of death
string Person::getDateOfDeath(){
    return DateOfDeath;
}
void Person::setDateOfDeath(string dod){
    DateOfDeath = dod;
}

// Get set country
string Person::getCountry(){
    return Country;
}

void Person::setCountry(string c){
    Country = c;
}

void Person::display(int nameLength) {
     cout << "| ";
     cout << setw(nameLength) << getName() << " | ";
     cout <<  setw(6) << getGender() << " | ";
     cout << setw(10) << getDateOfBirth() << " | ";
     cout << setw(10) << getDateOfDeath() << " | ";
     cout <<  setw(4) << getCountry() << endl;
}
