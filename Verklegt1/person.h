#ifndef PERSON
#define PERSON

#include <string>

class Person{
    std::string Name;
    std::string Gender;
    std::string DateOfBirth;
    std::string DateOfDeath;
public:
    // Constructor - Without date of death
    Person(std::string n, std::string g, std::string dob);
    
    // Constructor - With date of death
    Person(std::string n, std::string g, std::string dob, std::string dod);
    
    // Get set name
    std::string getName();
    void setName(std::string n);
    
    // Get set gender
    std::string getGender();
    void setGender(std::string g);
    
    // Get set date of birth
    std::string getDateOfBirth();
    void setDateOfBirth(std::string dob);
    
    // Get set date of death
    std::string getDateOfDeath();
    void setDateOfDeath(std::string dod);
};

#endif // PERSON

