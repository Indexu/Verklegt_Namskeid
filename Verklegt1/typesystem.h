#ifndef TYPESYSTEM_H
#define TYPESYSTEM_H
#include<string>

class TypeSystem{
    int Id;
    std::string Name;
public:
    // Constructor
    TypeSystem(int id, std::string name);

    // Get set ID
    int getId();
    void setId(int id);

    // Get set name
    std::string getName();
    void setName(std::string name);
};

#endif // TYPESYSTEM_H
