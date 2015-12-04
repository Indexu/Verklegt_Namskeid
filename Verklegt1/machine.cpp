#include "machine.h"

// Constructor
Machine::Machine(int id, std::string n, int y, bool b, std::string t, std::string s){
    Id = id;
    Name = n;
    Year = y;
    Built = b;
    type = t;
    system = s;
}

// GETTERS/SETTERS
// Get/set machine ID
int Machine::getId() {
    return Id;
}

void Machine::setId(int id) {
    Id = id;
}

// Get/set year build year
int Machine::getYear() {
    return Year;
}

void Machine::setYear(int y) {
    Year = y;
}

// Get/set if machine is built
bool Machine::isBuilt() {
    return Built;
}

void Machine::isBuilt(bool b) {
    Built = b;
}

// Get/set machine name
std::string Machine::getName() {
    return Name;
}

void Machine::setName(std::string n) {
    Name = n;
}

// Get/set machine type
std::string Machine::getType() {
    return type;
}

void Machine::setType(std::string t) {
    type = t;
}

// Get/set machine numerical system
std::string Machine::getSystem() {
    return system;
}

void Machine::setSystem(std::string s) {
    system = s;
}
