#include "typesystem.h"

// Constructor
TypeSystem::TypeSystem(int id, std::string name){
    Id = id;
    Name = name;
}

// Get ID
std::string TypeSystem::getId(){
    return Id;
}
// Set ID
void TypeSystem::setId(int id){
    Id = id;
}

// Get Name
std::string TypeSystem::getName(){
    return Name;
}
// Set Name
void TypeSystem::setName(int name){
    Name = name;
}

