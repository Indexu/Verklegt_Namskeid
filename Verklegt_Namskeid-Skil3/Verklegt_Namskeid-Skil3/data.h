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
    // Deconstructor
    ~Data();

    // Get database connection
    QSqlDatabase getDBCon();

    QVector<Person> getPersons();

    // Get person model
    QSqlTableModel *getPersonModel(QObject *parent);
    // Get machine model
    QSqlTableModel *getMachineModel(QObject *parent);
    // Get connection model
    QSqlTableModel *getConnectionModel(QObject *parent);
};

#endif // DATA_H
