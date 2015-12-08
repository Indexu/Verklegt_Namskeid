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
std::string getPersonsDB(std::vector<Person> &p, const char &sortColumn, const bool &desc);
// Get person by ID
std::string getPersonByIdDB(std::vector<Person> &p, const int &id);
// Add person
std::string addPersonDB(const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);
// Delete person
std::string delPersonDB(const int &id);
// Edit person
std::string editPersonDB(const int &id, const std::string &column, const std::string &value);
// Check if person ID exists
bool personIDExistsDB(const int &id, std::string &error);
// Search for a person
std::vector<Person> searchPersonDB(std::string &searchString, std::string &message, std::string &field, const std::__1::string &sorting, const bool &desc);

// == Machines ==
// Search for a machine
std::vector<Machine> searchMachineDB(std::string &searchString, std::string &message, std::string &field, const std::__1::string &sorting, const bool &desc);
// Get machines
std::string getMachinesDB(std::vector<Machine> &m, const char &sortColumn, const bool &desc);
// Get machine by ID
std::string getMachineByIdDB(std::vector<Machine> &m, const int &id);
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
std::string getTSDB(std::vector<TypeSystem> &t, const char &table, const char &sortColumn, const bool &desc);

// == Person Machine ==
// Get person machine connections
std::string getPersonMachineDB(std::vector<PersonMachine> &pm, const char &sortColumn, const bool &desc);
// Add person machine connections
std::string addPersonMachineDB(const int &p_id, const int &m_id);
// Check if connection exists
bool connectionPMExistsDB(const int &pid, const int &mid, std::string &error);
// Delete person machine connections
std::string delPersMachDB(const int &id);
// Check if connections ID exists
bool persMachConnectionIDExistsDB(const int &id, std::string &error);
// Get person-machine row by ID
std::string getPMByIdDB(std::vector<PersonMachine> &pm, const int &id);

#endif // DATA

