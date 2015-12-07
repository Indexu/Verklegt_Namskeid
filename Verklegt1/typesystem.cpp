#include "typesystem.h"

// Constructor
TypeSystem::TypeSystem(int id, std::string name){
    Id = id;
    Name = name;
}

// Get ID
int TypeSystem::getId() const{
    return Id;
}
// Set ID
void TypeSystem::setId(int id){
    Id = id;
}

// Get Name
std::string TypeSystem::getName() const{
    return Name;
}
// Set Name
void TypeSystem::setName(std::string name){
    Name = name;
}

