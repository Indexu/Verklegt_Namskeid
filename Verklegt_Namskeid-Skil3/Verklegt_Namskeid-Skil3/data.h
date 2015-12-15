#ifndef DATA_H
#define DATA_H

#include <QtSql>
#include "constants.h"
#include "person.h"
#include "machine.h"
#include "typesystem.h"
#include <QDebug>

class Data
{
    QSqlDatabase db;
public:
    // Constructor
    Data();
    // Deconstructor
    ~Data();

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
    bool deletePerson(const QVector<Person> &p, QString &error);
    // Edit person
    bool editPerson(const Person &p, QString &error);
    // Get person
    bool getPerson(Person &p, QString &error);
    // Check if person ID exists
    bool personIDExistsDB(const int &id, QString &error);

    // ==== Machines ====
    // Get all persons
    bool getAllMachines(QSqlQueryModel *machineQueryModel, QString &error);
    // Set the filter of machines
    bool filterMachine(QSqlQueryModel *machineQueryModel, const QString &filterStr, const QString &searchString, QString &error);
    // Add machine
    bool addMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error);
    // Delete machine
    bool deleteMachine(const QVector<Machine> &m, QString &error);
    // Get machine
    bool getMachine(Machine &m, QString &error);
    // Edit machine
    bool editMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error);
    // Check if machine ID exists
    bool machineIDExistsDB(const int &id, QString &error);

    // ==== Types / Systems ====
    // Get all types / systems
    bool getAllTypesSystems(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error);

    // ==== Connections ====
    // Get all connections
    bool getAllConnections(QSqlQueryModel *connectionQueryModel, QString &error);
    // Add connection
    bool addConnection(const int &p_id, const int &m_id, QString &error);
    // Check if connections exists
    bool connectionExists(const int &p_id, const int &m_id, QString &error);
};

#endif // DATA_H
