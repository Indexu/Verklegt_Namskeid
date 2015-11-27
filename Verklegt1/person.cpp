#include "person.h"

// Constructor - Without date of death
Person::Person(std::string n, std::string g, std::string dob){
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = "";
}

// Constructor - With date of death
Person::Person(std::string n, std::string g, std::string dob, std::string dod){
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = dod;
}

// Get set name
std::string Person::getName(){
    return Name;
}
void Person::setName(std::string n){
    Name = n;
}

// Get set gender
std::string Person::getGender(){
    return Gender;
}
void Person::setGender(std::string g){
    Gender = g;
}

// Get set date of birth
std::string Person::getDateOfBirth(){
    return DateOfBirth;
}
void Person::setDateOfBirth(std::string dob){
    DateOfBirth = dob;
}

// Get set date of death
std::string Person::getDateOfDeath(){
    return DateOfDeath;
}
void Person::setDateOfDeath(std::string dod){
    DateOfDeath = dod;
}
