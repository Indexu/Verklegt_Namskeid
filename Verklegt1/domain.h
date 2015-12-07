#ifndef DOMAIN_LAYER
#define DOMAIN_LAYER

#include "person.h"
#include "machine.h"
#include <vector>

// Start database
std::string startDB();

// Populate people
std::string populatePersonVector(std::vector<Person> &p, const std::string &sorting);

// Populate machine
std::string populateMachineVector(std::vector<Machine> &m, const std::string &sorting);

// List Persons
std::vector<Person> listPersons(std::string &command, std::string &message);

// List Machines
std::vector<Machine> listMachines(std::string &command, std::string &message);

// Searching for persons
std::vector<Person> callSearchPersonDB(std::string &query, std::string &message);

// Searching for machines
std::vector<Machine> callSearchMachineDB(std::string &query, std::string &message);

// Filter
std::vector<Person> filter(std::string &query, std::string &message);

// Verify date input
bool verifyDate(const std::string &ver);

// Add new person to DB
std::string addPerson(std::vector<Person> &p, const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);

// Delete person from DB
std::string delPerson(std::vector<Person> &p, std::string &command);

// Edit person in DB
std::string editPerson(std::vector<Person> &p, std::string command);

// Edit machine in DB
std::string editMachine(std::vector<Machine> &m, std::string command);

// Add new machine
std::string addMachine(std::vector<Machine> &m, const std::string &name, const std::string &year, const std::string &built, const std::string &type, const std::string &system);

// Delete machine
std::string delMachine(std::vector<Machine> &m, std::string &command);

#endif // DOMAIN_LAYER

