#ifndef PERSONMACHINE_H
#define PERSONMACHINE_H
#include <string>

class PersonMachine
{
    int Id;
    std::string P_Name;
    std::string P_Country;
    std::string M_Name;
    std::string M_Type;
    std::string M_System;
public:
    // Constructor
    PersonMachine(int id, std::string p_name, std::string p_country, std::string m_name, std::string m_type, std::string m_system);

    // Get set id
    int getId() const;
    void setId(int id);

    // Get set person name
    std::string getP_Name() const;
    void setP_Name(std::string p_name);

    // Get set person country
    std::string getP_Country() const;
    void setP_Country(std::string p_country);

    // Get set machine name
    std::string getM_Name() const;
    void setM_Name(std::string m_name);

    // Get set machine type
    std::string getM_Type() const;
    void setM_Type(std::string m_type);

    // Get set machine system
    std::string getM_System() const;
    void setM_System(std::string m_system);

    // Overload == operator
    bool operator==(const PersonMachine &p) const;
};

#endif // PERSONMACHINE_H
