#ifndef DATA_H
#define DATA_H

#include <QtSql>
#include "constants.h"
#include "person.h"

class Data
{
    QSqlDatabase db;
public:
    // Constructor
    Data();

    QSqlDatabase getDBCon();

    QVector<Person> getPersons();
};

#endif // DATA_H
