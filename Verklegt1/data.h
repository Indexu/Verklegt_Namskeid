#ifndef DATA
#define DATA

#include <vector>
#include "person.h"
#include "machine.h"

// Initialize DB
std::string initDB();
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
// Search for a machine
std::vector<Machine> searchMachineDB(std::string &searchString, std::string &message, std::string &field);
// Get machines
std::string getMachinesDB(std::vector<Machine> &m, const std::string &sorting);

#endif // DATA

