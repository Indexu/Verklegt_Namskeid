#ifndef UTILITY_H
#define UTILITY_H

#include "domain.h"
#include "data.h"
#include "person.h"
#include <vector>
#include <regex>


// Largest value in int vector
size_t largestValue(const std::vector<size_t> &v);

// Get command
std::string getCommand(const std::string &command);

// Get current id
int getCurrentId(const std::vector<Person> &p);

// Check if string is all-digits
bool isNumber(const std::string &str);

// Get index by ID
int getIndexByID(std::vector<Person> p, int id);

// Verify gender input
std::string verifyGender(std::string g);

// Converts arguments to strings
std::string convert2Field(std::string searchString);

#endif // UTILITY_H
