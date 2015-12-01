#include <QCoreApplication>
#include "presentation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "person.h"
#include <iomanip>
#include <regex>

using namespace std;

// Print data
void display(vector<Person> p, int longestName);
// Add data to vector
void populateVector(vector<Person> &p);
// Sort vector
bool sortNameAscend(Person p1, Person p2);
bool sortNameDescend(Person p1, Person p2);
// Get the longest name in the vector
int findLongestName(vector<Person> &p);
// Sort names
void sortNames(vector<Person> &p, string command, int longestName);
// Search for name
void search(vector<Person> &p, string query, int longestName);
// Verify date input
bool verifyDate(string ver);
// Find longest name in database
int findLongestName(vector<Person> &p);
// Add new person to vector
void add(vector<Person> &p);
// Help dialog
void help();
// Largest value in int vector
int largestValue(vector<int> &v);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== BEGIN =====

    loop();

    // ===== END =====
    return a.exec();
}
