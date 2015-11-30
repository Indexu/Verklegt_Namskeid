#ifndef PRESENTATION
#define PRESENTATION

#include <vector>
#include "person.h"

using namespace std;

// Main loop
void loop();
// Print data
void display(vector<Person> p, int longestName);
// Help dialog
void help(string command);

#endif // PRESENTATION

