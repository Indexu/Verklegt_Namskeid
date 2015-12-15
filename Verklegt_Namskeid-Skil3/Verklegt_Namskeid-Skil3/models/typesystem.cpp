#include "typesystem.h"

// Constructor
TypeSystem::TypeSystem(){
    Id = 0;
    Name = "";
}

TypeSystem::TypeSystem(int id, QString name){
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
QString TypeSystem::getName() const{
    return Name;
}
// Set Name
void TypeSystem::setName(QString name){
    Name = name;
}

