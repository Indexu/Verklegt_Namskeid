#ifndef DOMAIN_LAYER
#define DOMAIN_LAYER

#include "person.h"
#include "machine.h"
#include "typesystem.h"
#include "personmachine.h"
#include <vector>

// Start database
std::string startDB();

// Populate people
std::string populatePersonVector(std::vector<Person> &p, const char &sortColumn, const bool &desc);

// Populate machine
std::string populateMachineVector(std::vector<Machine> &m, const char &sortColumn, const bool &desc);

// Populate types and systems
std::string populateTSVector(std::vector<TypeSystem> &ts, const char &table, const char &sortColumn, const bool &desc);

// Populate person machine
std::string populatePMVector(std::vector<PersonMachine> &pm, const char &sortColumn, const bool &desc);

// List Persons
std::vector<Person> listPersons(std::string &command, std::string &message);

// List Machines
std::vector<Machine> listMachines(std::string &command, std::string &message);

// List Types and Systems
std::vector<TypeSystem> listTS(std::string &command, std::string &message);

// List Persons and Machines
std::vector<PersonMachine> listPM(std::string &command, std::string &message);

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

// Connect person and machine
std::string conPM(const std::vector<Person> &p, const std::vector<Machine> &m, const std::string &command);

// Delete connection person machine
std::string delPM(std::vector<PersonMachine> &pm, std::string &command);

#endif // DOMAIN_LAYER

