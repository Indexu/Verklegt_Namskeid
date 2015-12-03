#ifndef DOMAIN_LAYER
#define DOMAIN_LAYER

#include "person.h"
#include <vector>

// Start database
std::string startDB();

// Add data to vector
std::string populateVector(std::vector<Person> &p);

// Sort vector
bool sortNameAscend(const Person p1, const Person p2);
bool sortNameDescend(const Person p1, const Person p2);
bool sortByIdAscend(const Person p1, const Person p2);
bool sortByIdDescend(const Person p1, const Person p2);

// Get the longest name in the vector
int findLongestName(const std::vector<Person> &p);

// Sort names
void sortNames(std::vector<Person> &p, const std::string &command);

// Search
std::vector<Person> search(const std::vector<Person> &p, std::string &query, std::string &message);

// Filter
std::vector<Person> filter(const std::vector<Person> &p, std::string &query, std::string &message);

// Verify date input
bool verifyDate(const std::string &ver);

// Add new person to DB
std::string addPerson(std::vector<Person> &p, const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);

// Delete person from DB
std::string del(std::vector<Person> &p, std::string &command);

// Edit person in DB
std::string edit(std::vector<Person> &p, std::string command);

#endif // DOMAIN_LAYER

