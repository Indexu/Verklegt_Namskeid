#ifndef DATA
#define DATA

#include <vector>
#include "person.h"

std::string initDB();
std::string getPersonsDB(std::vector<Person> &p, const std::string &sorting);
std::string addPersonDB(const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);
std::string delPersonDB(const int &id);
std::string editPersonDB(const int &id, const std::string &column, const std::string &value);
bool personIDExistsDB(const int &id, std::string &error);
std::vector<Person> searchPersonDB(std::string &searchString, std::string &message, std::string &field);

#endif // DATA

