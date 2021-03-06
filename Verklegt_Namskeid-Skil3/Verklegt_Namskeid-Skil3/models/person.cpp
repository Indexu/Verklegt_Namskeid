#include "person.h"

// Default
Person::Person(){
    Id = 0;
    Name = "";
    Gender = "";
    DateOfBirth = "";
    DateOfDeath = "";
    Country = "";
}

// Constructor - without ID
Person::Person(QString n, QString g, QString dob, QString dod, QString c){
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = dod;
    Country = c;
}

// Constructor - with ID
Person::Person(int i, QString n, QString g, QString dob, QString dod, QString c){
    Id = i;
    Name = n;
    Gender = g;
    DateOfBirth = dob;
    DateOfDeath = dod;
    Country = c;
}

// Get set ID
int Person::getId() const{
    return Id;
}
void Person::setId(int i){
    Id = i;
}

// Get set name
QString Person::getName() const{
    return Name;
}
void Person::setName(QString n){
    Name = n;
}

// Get set gender
QString Person::getGender() const{
    return Gender;
}
void Person::setGender(QString g){
    Gender = g;
}

// Get set date of birth
QString Person::getDateOfBirth() const{
    return DateOfBirth;
}
void Person::setDateOfBirth(QString dob){
    DateOfBirth = dob;
}

// Get set date of death
QString Person::getDateOfDeath() const{
    return DateOfDeath;
}
void Person::setDateOfDeath(QString dod){
    DateOfDeath = dod;
}

// Get set country
QString Person::getCountry() const{
    return Country;
}
void Person::setCountry(QString c){
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

// Operator =
void Person::operator=(const Person &p){
    Id = p.getId();
    Name = p.getName();
    Gender = p.getGender();
    DateOfBirth = p.getDateOfBirth();
    DateOfDeath = p.getDateOfDeath();
    Country = p.getCountry();
}
