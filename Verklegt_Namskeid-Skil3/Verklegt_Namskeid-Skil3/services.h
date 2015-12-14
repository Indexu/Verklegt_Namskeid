#ifndef SERVICES_H
#define SERVICES_H

#include <QSqlQueryModel>
#include "data.h"
#include "person.h"
#include "machine.h"

class Services
{
    // Data layer instance
    Data dataLayer;
public:
    // Constructor
    Services();

    // Get person model from data layer
    QSortFilterProxyModel *getPersonModel(QSqlQueryModel *&personQueryModel);
    // Get machine model from data layer
    QSortFilterProxyModel* getMachineModel(QSqlQueryModel *&machineQueryModel);
    // Get connection model from data layer
    QSortFilterProxyModel *getConnectionModel(QSqlQueryModel *&connectionQueryModel);

    // ==== Persons ====
    // Get all persons
    bool getAllPersons(QSqlQueryModel *personQueryModel, QString &error);
    // Search person
    bool searchPerson(QSqlQueryModel *personQueryModel, const QString &searchString, const int &column, QString &error);
    // Filter person
    bool filterPerson(QSqlQueryModel *personQueryModel, const QString &searchString, const int &column, QString &error);
    // Add person
    bool addPerson(const Person &p, QString &error);
    // Delete person
    bool deletePerson(const QVector<Person> &p, QString &error);
    // Edit person
    bool editPerson(const Person &p, QString &error);
    // Get person
    bool getPerson(Person &p, QString &error);

    // ==== Machines ====
    // Get all persons
    bool getAllMachines(QSqlQueryModel *machineQueryModel, QString &error);
    // Search machine
    bool searchMachine(QSqlQueryModel *machineQueryModel, const QString &searchString, const int &column, QString &error);
    // Filter machine
    bool filterMachine(QSqlQueryModel *machineQueryModel, const QString &searchString, const int &column, QString &error);
    // Add machine
    bool addMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error);
    // Delete machine
    bool deleteMachine(const QVector<Machine> &m, QString &error);
    // Get machine
    bool getMachine(Machine &m, QString &error);

    // ==== Types and Systems ====
    bool getAllTypesSystems(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error);
};

#endif // SERVICES_H
