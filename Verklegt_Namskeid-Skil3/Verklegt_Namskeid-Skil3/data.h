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

    // Get all persons
    bool getAllPersons(QSqlTableModel *personModel, QString &error);

    // Set the filter of persons
    void setFilterPerson(QSqlTableModel *personModel, const QString &filterStr, const QString &searchString, QString &error);

    // Add person
    bool addPerson(const Person &p, QString &error);
    // Delete person
    bool deletePerson(const int &id, QString &error);

    // Check if person ID exists
    bool personIDExistsDB(const int &id, QString &error);
};

#endif // DATA_H
