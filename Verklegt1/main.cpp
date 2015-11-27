#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include "person.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person alan("Alan Turing", "male", "21/05/1926");

    cout << alan.getName() << endl;
    cout << alan.getGender() << endl;
    cout << alan.getDateOfBirth() << endl;

    return a.exec();
}

