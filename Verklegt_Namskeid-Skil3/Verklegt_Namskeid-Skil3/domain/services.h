#ifndef SERVICES_H
#define SERVICES_H

#include <QSqlQueryModel>
#include "data/data.h"
#include "models/person.h"
#include "models/machine.h"
#include "models/personmachine.h"
#include "models/typesystem.h"

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
    // Get type model from data layer
    QSortFilterProxyModel *getTypeModel(QSqlQueryModel *&typeQueryModel);
    // Get system model from data layer
    QSortFilterProxyModel *getSystemModel(QSqlQueryModel *&systemQueryModel);

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
    // Edit machine
    bool editMachine(Machine &m, const int &type_id, const int &sys_id, QString &error);

    // ==== Connections ====
    // Get all connections
    bool getAllConnections(QSqlQueryModel *connectionQueryModel, QString &error);
    // Add connection
    bool addConnection(const int &p_id, const int &m_id, QString &error);
    // Delete connection
    bool deleteConnection(const QVector<PersonMachine> &pm, QString &error);
    // Search connection
    bool searchConnection(QSqlQueryModel *connectionQueryModel, const QString &searchString, const int &column, QString &error);
    // Filter connection
    bool filterConnection(QSqlQueryModel *connectionQueryModel, const QString &searchString, const int &column, QString &error);
    // Get Connection
    bool getConnection(PersonMachine &pm, QString error);

    // ==== Types ====
    // Get all types
    bool getAllTypesSystems(QSqlQueryModel *typeQueryModel, QString &error);
    // Get all systems
    bool getAllSystems(QSqlQueryModel *systemQueryModel, QString &error);
    // Search type
    bool searchType(QSqlQueryModel *typeQueryModel, const QString &searchString, const int &column, QString &error);
    // Filter type
    bool filterType(QSqlQueryModel *typeQueryModel, const QString &searchString, const int &column, QString &error);
    // Search system
    bool searchSystem(QSqlQueryModel *systemQueryModel, const QString &searchString, const int &column, QString &error);
    // Filter system
    bool filterSystem(QSqlQueryModel *systemQueryModel, const QString &searchString, const int &column, QString &error);
    // Add type / system
    bool addTypeSystem(const QString &ts, const bool &type, QString &error);
    // Delete type / system
    bool deleteTypeSystem(const QVector<TypeSystem> &ts, const bool &type, QString &error);
    // Get type / system
    bool getTypeSystem(TypeSystem &ts, const bool &type, QString &error);
    // Edit type / system
    bool editTypeSystem(const TypeSystem &ts, const bool &type, QString &error);

    // ==== Types / Systems ====
    // Get all types / systems
    bool getAllTypesSystemsVector(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error);
};

#endif // SERVICES_H
