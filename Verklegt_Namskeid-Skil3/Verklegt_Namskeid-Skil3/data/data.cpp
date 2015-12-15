#include "data.h"

// Constructor
Data::Data(){
    // If connection has already been made, return the connection
    if(QSqlDatabase::contains(constants::CON_NAME))
    {
        db = QSqlDatabase::database(constants::CON_NAME);
    }
    // Make new connection
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", constants::CON_NAME);
        db.setDatabaseName(constants::DB_NAME);

        db.open();
    }
}

// Deconstructor
Data::~Data(){
    db.close();
}

// ==== MODELS ====
// Create and return person model
QSortFilterProxyModel *Data::getPersonModel(QSqlQueryModel *&personQueryModel){

    // Initialize Query model
    personQueryModel = new QSqlQueryModel();

    // Initial data
    personQueryModel->setQuery("SELECT * FROM persons", db);

    // Create proxy model for sorting
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(personQueryModel);

    // Return
    return proxy;
}

// Create and return machine model
QSortFilterProxyModel *Data::getMachineModel(QSqlQueryModel *&machineQueryModel){

    // Initialize Query model
    machineQueryModel = new QSqlQueryModel();

    // Initial data
    machineQueryModel->setQuery("SELECT * FROM machinesView", db);

    // Create proxy model for sorting
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(machineQueryModel);

    // Return
    return proxy;
}

// Create and return connection model
QSortFilterProxyModel *Data::getConnectionModel(QSqlQueryModel *&connectionQueryModel){
    // Initialize Query model
    connectionQueryModel = new QSqlQueryModel();

    // Initial data
    connectionQueryModel->setQuery("SELECT * FROM pers_machView", db);

    // Create proxy model for sorting
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(connectionQueryModel);

    // Return
    return proxy;
}
