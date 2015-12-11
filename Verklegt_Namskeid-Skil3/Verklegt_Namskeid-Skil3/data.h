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
    QSqlQueryModel *getPersonModel();
    // Get machine model
    QSqlQueryModel *getMachineModel();
    // Get connection model
    QSqlQueryModel *getConnectionModel();

    // Get all persons
    bool getAllPersons(QSqlQueryModel *personModel, QString &error);

    // Set the filter of persons
    bool filterPerson(QSqlQueryModel *personModel, const QString &filterStr, const QString &searchString, QString &error);

    // Add person
    bool addPerson(const Person &p, QString &error);
    // Delete person
    bool deletePerson(const int &id, QString &error);
    // Edit person
    bool editPerson(const Person &p, QString &error);

    // Get person
    bool getPerson(Person &p, QString &error);

    // Check if person ID exists
    bool personIDExistsDB(const int &id, QString &error);
};

#endif // DATA_H
