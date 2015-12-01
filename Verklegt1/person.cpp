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
string Person::getName() const{
    return Name;
}
void Person::setName(std::string n){
    Name = n;
}

// Get set gender
string Person::getGender() const{
    return Gender;
}
void Person::setGender(string g){
    Gender = g;
}

// Get set date of birth
string Person::getDateOfBirth() const{
    return DateOfBirth;
}
void Person::setDateOfBirth(string dob){
    DateOfBirth = dob;
}

// Get set date of death
string Person::getDateOfDeath() const{
    return DateOfDeath;
}
void Person::setDateOfDeath(string dod){
    DateOfDeath = dod;
}

// Get set country
string Person::getCountry() const{
    return Country;
}
void Person::setCountry(string c){
    Country = c;
}

// Operator ==
bool Person::operator==(const Person &p) const{
    bool n = (Name == p.getName());
    bool g = (Gender == p.getGender());
    bool b = (DateOfBirth == p.getDateOfBirth());
    bool d = (DateOfDeath == p.getDateOfDeath());
    bool c = (Country == p.getCountry());

    return (n && g && b && d && c);
}
