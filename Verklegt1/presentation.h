#ifndef PRESENTATION
#define PRESENTATION

#include <vector>
#include "person.h"

// Constant for table length when displaying
int const TABLE_LENGTH = 54;

// Main loop
void loop();

// Print data
void display(std::vector<Person> p, int longestName);

// Help dialog
void help(std::string command);

// Clear screen
void clearScreen();

#endif // PRESENTATION


