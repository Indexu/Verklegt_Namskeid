#include "machine.h"


Machine::Machine(int id, int y, bool b, std::string n, std::string t){
    Id = id;
    Year = y;
    Built = b;
    Name = n;
    MType_ID = t;
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
    return MType_ID;
}

void Machine::setType(std::string id) {
    MType_ID = id;
}
