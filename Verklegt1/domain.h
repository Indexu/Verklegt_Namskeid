#ifndef DOMAIN
#define DOMAIN

#include <vector>
#include <regex>

using namespace std;

// Add data to vector
void populateVector(vector<Person> &p);
// Sort vector
bool sortNameAscend(Person p1, Person p2);
bool sortNameDescend(Person p1, Person p2);
// Get the longest name in the vector
int findLongestName(vector<Person> &p);
// Sort names
void sortNames(vector<Person> &p, string command);
// Search for name
vector<Person> search(vector<Person> &p, string query, string &message);
// Verify date input
bool verifyDate(string ver);
// Find longest name in database
int findLongestName(vector<Person> &p);
// Add new person to vector
void add(vector<Person> &p);
// Largest value in int vector
int largestValue(vector<int> &v);

#endif // DOMAIN

