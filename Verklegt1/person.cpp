#include "person.h"

// Constructor
Person::Person(int id, std::string n, std::string g, std::string dob, std::string dod, std::string c){
    Id = id;
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = dod;
    Country = c;
}

// Get id
int Person::getId() const{
    return Id;
}

// Get set name
std::string Person::getName() const{
    return Name;
}
void Person::setName(std::string n){
    Name = n;
}

// Get set gender
std::string Person::getGender() const{
    return Gender;
}
void Person::setGender(std::string g){
    Gender = g;
}

// Get set date of birth
std::string Person::getDateOfBirth() const{
    return DateOfBirth;
}
void Person::setDateOfBirth(std::string dob){
    DateOfBirth = dob;
}

// Get set date of death
std::string Person::getDateOfDeath() const{
    return DateOfDeath;
}
void Person::setDateOfDeath(std::string dod){
    DateOfDeath = dod;
}

// Get set country
std::string Person::getCountry() const{
    return Country;
}
void Person::setCountry(std::string c){
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
