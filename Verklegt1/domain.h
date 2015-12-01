#ifndef DOMAIN_LAYER
#define DOMAIN_LAYER

#include "person.h"
#include <vector>

// Add data to vector
void populateVector(std::vector<Person> &p, std::string &message);

// Sort vector
bool sortNameAscend(const Person p1, const Person p2);
bool sortNameDescend(const Person p1, const Person p2);

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

// Add new person to vector
void add(std::vector<Person> &p);

// Largest value in int vector
int largestValue(const std::vector<int> &v);

// Add to txt file
void writeVector(const std::vector<Person> &p);

// Get command
std::string getCommand(const std::string &command);

#endif // DOMAIN_LAYER

