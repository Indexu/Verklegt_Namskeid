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
    return type;
}

void Machine::setType(std::string t) {
    type = t;
}

// Get/set machine numerical system
std::string Machine::getSystem() const{
    return system;
}

void Machine::setSystem(std::string s) {
    system = s;
}
