#include "machine.h"

// Constructor
Machine::Machine(int id, std::string n, int y, bool b, std::string t, std::string s){
    Id = id;
    Name = n;
    Year = y;
    Built = b;
    Type = t;
    System = s;
}

// GETTERS/SETTERS
// Get/set machine ID
int Machine::getId() const {
    return Id;
}

void Machine::setId(int id) {
    Id = id;
}

// Get/set year build year
int Machine::getYear() const{
    return Year;
}

void Machine::setYear(int y) {
    Year = y;
}

// Get/set if machine is built
bool Machine::getBuilt() const{
    return Built;
}

void Machine::setBuilt(bool b) {
    Built = b;
}

// Get/set machine name
std::string Machine::getName() const{
    return Name;
}

void Machine::setName(std::string n) {
    Name = n;
}

// Get/set machine type
std::string Machine::getType() const{
    return Type;
}

void Machine::setType(std::string t) {
    Type = t;
}

// Get/set machine numerical system
std::string Machine::getSystem() const{
    return System;
}

void Machine::setSystem(std::string s) {
    System = s;
}

// Operator ==
bool Machine::operator==(const Machine &m) const{
    bool n = (Name == m.getName());
    bool y = (Year == m.getYear());
    bool b = (Built == m.getBuilt());
    bool t = (Type == m.getType());
    bool s = (System == m.getSystem());

    return (n && y && b && t && s);
}
