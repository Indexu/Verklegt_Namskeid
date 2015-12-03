#ifndef DATA
#define DATA

#include <vector>
#include "person.h"

void getData(std::vector<Person> &p, std::string &message);
void addPersonDB(const std::string &name, const std::string &gender, const std::string &dob, const std::string &dod, const std::string &country);

#endif // DATA

