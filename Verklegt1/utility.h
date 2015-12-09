#ifndef UTILITY_H
#define UTILITY_H

#include "domain.h"
#include "data.h"
#include "person.h"
#include <vector>
#include <regex>


// Largest value in int vector
size_t largestValue(const std::vector<size_t> &v);

// Get the longest name in Person vector
int findLongestPName(const std::vector<Person> &p);

// Get longest name in Machine vector
int findLongestMName(const std::vector<Machine> &m);

// Get longest type in Machine vector
int findLongestMType(const std::vector<Machine> &m);

// Get longest typesystem name
int findLongestTSName(const std::vector<TypeSystem> &ts);

// Verify date input
bool verifyDate(const std::string &ver);

// Get command
std::string getCommand(const std::string &command);

// Get current id
int getCurrentId(const std::vector<Person> &p);

// Check if string is all-digits
bool isNumber(const std::string &str);

// Get person index by ID
int getPIndexByID(std::vector<Person> p, int id);

// Get machine index by ID
int getMIndexByID(std::vector<Machine> m, int id);

// Verify gender input
std::string verifyGender(std::string g);

// Converts arguments to strings
std::string convert2Field(std::string searchString, std::string database);

// Split string
std::vector<std::string> splitString(std::string input, std::string delim);

// Get arguments
std::vector<std::string> getArgs(std::string query);

// Assemble a string
std::string assembleString(std::vector<std::string> inputVect, std::string delim);

// Converts 1's and 0's to yes/no
std::string boolYesNo(bool num);

// y/n string to bool
bool stringBool(std::string s);

// Parse search command
std::string parseSearchArgs(std::string &query, std::string &searchString, std::vector<std::string> &arguments, std::string &arg, std::string &sort, bool &desc, const std::string &db);

// Get command without value
std::string getNoValueCommand(std::string query);

#endif // UTILITY_H
