#include "personmachine.h"

// Constructor
PersonMachine::PersonMachine(int id, std::string p_name, std::string p_country, std::string m_name, std::string m_type, std::string m_system){
    Id = id;
    P_Name = p_name;
    P_Country = p_country;
    M_Name = m_name;
    M_Type = m_type;
    M_System = m_system;
}

// Get set id
int PersonMachine::getId() const{
    return Id;
}

void PersonMachine::setId(int id){
    Id = id;
}

// Get set person name
std::string PersonMachine::getP_Name() const{
    return P_Name;
}

void PersonMachine::setP_Name(std::string p_name){
    P_Name = p_name;
}

// Get set person country
std::string PersonMachine::getP_Country() const{
    return P_Country;
}

void PersonMachine::setP_Country(std::string p_country){
    P_Country = p_country;
}

// Get set machine name
std::string PersonMachine::getM_Name() const{
    return M_Name;
}

void PersonMachine::setM_Name(std::string m_name){
    M_Name = m_name;
}

// Get set machine type
std::string PersonMachine::getM_Type() const{
    return M_Type;
}
void PersonMachine::setM_Type(std::string m_type){
    M_Type = m_type;
}

// Get set machine system
std::string PersonMachine::getM_System() const{
    return M_System;
}
void PersonMachine::setM_System(std::string m_system){
    M_System = m_system;
}

// Operator ==
bool PersonMachine::operator==(const PersonMachine &pm) const{
    bool pn = (P_Name == pm.getP_Name());
    bool mn = (M_Name == pm.getM_Name());
    bool c = (P_Country == pm.getP_Country());
    bool t = (M_Type == pm.getM_Type());
    bool s = (M_System == pm.getM_System());

    return (pn && mn && c && t && s);
}
