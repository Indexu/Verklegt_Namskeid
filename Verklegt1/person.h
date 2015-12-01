#ifndef PERSON
#define PERSON

#include <string>
#include <iostream>
#include <vector>

class Person{
    int Id;
    std::string Name;
    std::string Gender;
    std::string DateOfBirth;
    std::string DateOfDeath;
    std::string Country;
public:
    // Constructor - With date of death
    Person(int id, std::string n, std::string g, std::string dob, std::string dod, std::string c);

    // Get id
    int Person::getId() const;
    
    // Get set name
    std::string getName() const;
    void setName(std::string n);
    
    // Get set gender
    std::string getGender() const;
    void setGender(std::string g);

    // Get set date of birth
    std::string getDateOfBirth() const;
    void setDateOfBirth(std::string dob);
    
    // Get set date of death
    std::string getDateOfDeath() const;
    void setDateOfDeath(std::string dod);

    // Get set country
    std::string getCountry() const;
    void setCountry(std::string c);

    // Overload == operator
    bool operator==(const Person &p) const;

};

#endif // PERSON

