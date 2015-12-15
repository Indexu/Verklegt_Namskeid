#ifndef DATA_H
#define DATA_H

#include <QtSql>
#include "utilities/constants.h"
#include "models/person.h"
#include "models/machine.h"
#include "models/personmachine.h"
#include "models/typesystem.h"
#include <QDebug>

class Data
{
    QSqlDatabase db;
public:
    // Constructor
    Data();
    // Deconstructor
    ~Data();

    // Check to see if DB contains necessary tables
    void checkDB();
    // Create all the tables and views
    void setupDB();

    // ==== MODELS ====
    // Get person model
    QSortFilterProxyModel *getPersonModel(QSqlQueryModel *&personQueryModel);
    // Get machine model
    QSortFilterProxyModel *getMachineModel(QSqlQueryModel *&machineQueryModel);
    // Get connection model
    QSortFilterProxyModel *getConnectionModel(QSqlQueryModel *&connectionQueryModel);
    // Get type model
    QSortFilterProxyModel *getTypeModel(QSqlQueryModel *&typeQueryModel);
    // Get system model
    QSortFilterProxyModel *getSystemModel(QSqlQueryModel *&systemQueryModel);

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

    // ==== Connections ====
    // Get all connections
    bool getAllConnections(QSqlQueryModel *connectionQueryModel, QString &error);
    // Add connection
    bool addConnection(const int &p_id, const int &m_id, QString &error);
    // Delete connection
    bool deleteConnection(const QVector<PersonMachine> &pm, QString &error);
    // Check if connections exists
    bool connectionExists(const int &p_id, const int &m_id, QString &error);
    // Set the filter of connections
    bool filterConnection(QSqlQueryModel *connectionQueryModel, const QString &filterStr, const QString &searchString, QString &error);
    // Check if pers_mach ID exists in DB
    bool connectionIDExistsDB(const int &id, QString &error);
    // Get Connection
    bool getConnection(PersonMachine &pm, QString error);

    // ==== Types / Systems ====
    // Get all types
    bool getAllTypes(QSqlQueryModel *typeQueryModel, QString &error);
    // Get all systems
    bool getAllSystems(QSqlQueryModel *systemQueryModel, QString &error);
    // Set the filter of type
    bool filterType(QSqlQueryModel *typeQueryModel, const QString &filterStr, const QString &searchString, QString &error);
    // Set the filter of system
    bool filterSystem(QSqlQueryModel *systemQueryModel, const QString &filterStr, const QString &searchString, QString &error);
    // Add type / system
    bool addTypeSystem(const QString &ts, const bool &type, QString &error);
    // Delete type / system
    bool deleteTypeSystem(const QVector<TypeSystem> &ts, const bool &type, QString &error);
    // Get type / system
    bool getTypeSystem(TypeSystem &ts, const bool &type, QString &error);
    // Edit type / system
    bool editTypeSystem(const TypeSystem &ts, const bool &type, QString &error);
    // Check if type / system ID exists in DB
    bool typeSystemIDExistsDB(const int &id, const bool &type, QString &error);

    // Get all types / system into vector
    bool getAllTypesSystemsVector(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error);
};

#endif // DATA_H
