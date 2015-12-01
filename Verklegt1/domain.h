#ifndef DOMAIN_LAYER
#define DOMAIN_LAYER

#include "person.h"
#include <vector>

// Add data to vector
void populateVector(std::vector<Person> &p, std::string &message);

// Sort vector
bool sortNameAscend(Person p1, Person p2);
bool sortNameDescend(Person p1, Person p2);

// Get the longest name in the vector
int findLongestName(std::vector<Person> &p);

// Sort names
void sortNames(std::vector<Person> &p, std::string command);

// Search for name
std::vector<Person> search(std::vector<Person> &p, std::string query, std::string &message);

// Verify date input
bool verifyDate(std::string ver);

// Find longest name in database
int findLongestName(std::vector<Person> &p);

// Add new person to vector
void add(std::vector<Person> &p);

// Largest value in int vector
int largestValue(std::vector<int> &v);

// Add to txt file
void addInfo(std::vector<Person> &p);

// Get command
std::string getCommand(std::string command);

#endif // DOMAIN_LAYER

