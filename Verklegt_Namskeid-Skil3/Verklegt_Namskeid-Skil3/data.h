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

    // ==== MODELS ====
    // Get person model
    QSortFilterProxyModel *getPersonModel(QSqlQueryModel *&personQueryModel);
    // Get machine model
    QSortFilterProxyModel *getMachineModel(QSqlQueryModel *&machineQueryModel);
    // Get connection model
    QSortFilterProxyModel *getConnectionModel(QSqlQueryModel *&connectionQueryModel);

    // ==== Person ====
    // Get all persons
    bool getAllPersons(QSqlQueryModel *personQueryModel, QString &error);
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

    // ==== Machines ====
    // Get all persons
    bool getAllMachines(QSqlQueryModel *machineQueryModel, QString &error);
};

#endif // DATA_H
