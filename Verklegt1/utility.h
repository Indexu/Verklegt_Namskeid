#ifndef UTILITY_H
#define UTILITY_H

#include "domain.h"
#include "data.h"
#include "person.h"
#include <vector>
#include <regex>


// Largest value in int vector
int largestValue(const std::vector<int> &v);

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


#endif // UTILITY_H
