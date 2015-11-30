#ifndef PERSON
#define PERSON

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class Person{
    std::string Name;
    std::string Gender;
    std::string DateOfBirth;
    std::string DateOfDeath;
    std::string Country;
public:
    // Constructor - With date of death
    Person(std::string n, std::string g, std::string dob, std::string dod, std::string c);
    
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

    // Get set country
    std::string getCountry();
    void setCountry(std::string c);

    // Get longest name
    int getLongestName();

    // Set longest name
    void setLongestName(int n);

    // Display the vector
    void display(int nameLength);

};

#endif // PERSON

