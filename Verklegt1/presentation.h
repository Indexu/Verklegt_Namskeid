#ifndef PRESENTATION
#define PRESENTATION

#include <vector>
#include "person.h"

// Main loop
void loop();

// Print data
void display(std::vector<Person> p, int longestName);

// Help dialog
void help(std::string command);

#endif // PRESENTATION

