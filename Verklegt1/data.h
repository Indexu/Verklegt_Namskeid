#ifndef DATA
#define DATA

#include <vector>
#include "person.h"
#include "machine.h"
#include "typesystem.h"
#include "personmachine.h"

// Initialize DB
std::string initDB();

// == Persons ==
// Get persons
std::string getPersonsDB(std::vector<Person> &p, const std::string &sorting);
// Add person
std::string addPersonDB(const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);
// Delete person
std::string delPersonDB(const int &id);
// Edit person
std::string editPersonDB(const int &id, const std::string &column, const std::string &value);
// Check if person ID exists
bool personIDExistsDB(const int &id, std::string &error);
// Search for a person
std::vector<Person> searchPersonDB(std::string &searchString, std::string &message, std::string &field);

// == Machines ==
// Search for a machine
std::vector<Machine> searchMachineDB(std::string &searchString, std::string &message, std::string &field);
// Get machines
std::string getMachinesDB(std::vector<Machine> &m, const std::string &sorting);
// Add machine
std::string addMachineDB(const std::string &name, const std::string &year, const std::string &built, const std::string &type, const std::string &system);
// Delete machine
std::string delMachineDB(const int &id);
// Edit machine
std::string editMachineDB(const int &id, const std::string &column, const std::string &value);
// Check if machine ID exists
bool machineIDExistsDB(const int &id, std::string &error);

// == Types and Systems ==
// Get types and systems
std::string getTSDB(std::vector<TypeSystem> &t, const std::string &table, const std::string &sorting);

// == Person Machine ==
// Get person machine connections
std::string getPersonMachineDB(std::vector<PersonMachine> &pm, const std::string &sorting);
// Add person machine connections
std::string addPersonMachineDB(const int &p_id, const int &m_id);
// Check if connection exists
bool connectionPMExistsDB(const int &pid, const int &mid, std::string &error);

#endif // DATA

