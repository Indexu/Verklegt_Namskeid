#ifndef PRESENTATION
#define PRESENTATION

#include <vector>
#include "person.h"
#include "machine.h"

// Constant for table length when displaying
int const TABLE_LENGTH = 54;

// Main loop
void loop();

// Print person
void displayPerson(std::vector<Person> p, int longestName);

// Print machine
void displayMachine(const std::vector<Machine> &m, const int &longestMName, const int &longestMType);

// Help dialog
void help(std::string command);

// Add process for persons
void addProcessPerson(std::vector<Person> &p);

// Add process for machines
void addProcessMachine(std::vector<Machine> &m);

// Clear screen
void clearScreen();

#endif // PRESENTATION


