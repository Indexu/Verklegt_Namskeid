#ifndef MACHINE_H
#define MACHINE_H
#include <string>

class Machine
{
    int Id;
    std::string Name;
    int Year;
    bool Built;
    std::string type;
public:
    // Constructor
    Machine(int id, std::string n, int y, bool b, std::string t);

    // GETTERS/SETTERS
    // Get/set machine ID
    int getId();
    void setId(int id);

    // Get/set year build year
    int getYear();
    void setYear(int y);

    // Get/set if machine is built
    bool isBuilt();
    void isBuilt(bool b);

    // Get/set machine name
    std::string getName();
    void setName(std::string n);

    // Get/set machine type
    std::string getType();
    void setType(std::string t);

};

#endif // MACHINE_H

