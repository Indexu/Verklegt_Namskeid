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

        checkDB();
    }
}

// Deconstructor
Data::~Data(){
    db.close();
}

// Check for tables
void Data::checkDB(){
    if(db.isOpen()){
        QSqlQuery query(db);

        query.prepare("SELECT * FROM sqlite_master");

        query.exec();

        // Count tables
        int tableCount = 0;
        while(query.next()){
            if (query.value("type").toString() == "table"){
                tableCount++;
            }
        }

        // Setup if necessary
        if(tableCount != 6){
            setupDB();
        }
    }
}

// Create the tables and views
void Data::setupDB(){
    if(db.open()){
        QSqlQuery query(db);

        // Persons
        QString create = "CREATE TABLE 'persons' "
                         "("
                         "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE , "
                         "'name' TEXT NOT NULL , "
                         "'gender' TEXT NOT NULL , "
                         "'date_of_birth' TEXT NOT NULL , "
                         "'date_of_death' TEXT, "
                         "'country' TEXT NOT NULL "
                         ")";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Machine types
        create = "CREATE TABLE 'mtype' "
                 "("
                 "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE , "
                 "'name' TEXT NOT NULL "
                 ")";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Machine number systems
        create = "CREATE TABLE 'num_sys' "
                 "("
                 "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE , "
                 "'name' TEXT NOT NULL "
                 ")";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Machines
        create = "CREATE TABLE 'machines' "
                 "("
                 "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                 "'name' TEXT NOT NULL, "
                 "'year' TEXT DEFAULT ('-') NOT NULL,"
                 "'built' BOOL NOT NULL, "
                 "'mtype_id' INTEGER NOT NULL, "
                 "'num_sys_id' INTEGER NOT NULL, "
                 "FOREIGN KEY(mtype_id) REFERENCES mtype(id), "
                 "FOREIGN KEY(num_sys_id) REFERENCES num_sys(id)"
                 ")";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Person Machine relations table
        create = "CREATE TABLE 'pers_mach' "
                 "("
                 "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE ,"
                 "'p_id' INTEGER , "
                 "'m_id' INTEGER , "
                 "FOREIGN KEY(p_id) REFERENCES persons(id), "
                 "FOREIGN KEY(m_id) REFERENCES machines(id)"
                 ")";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Machines view
        create = "CREATE VIEW 'machinesView' AS "
                 "SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                 "machines.built AS built, mtype.name AS type, num_sys.name AS system "
                 "FROM machines "
                 "JOIN mtype ON (machines.mtype_id=mtype.id) "
                 "JOIN num_sys ON (machines.num_sys_id=num_sys.id)";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Person Machine relations view
        create = "CREATE VIEW 'pers_machView' AS "
                 "SELECT pers_mach.id AS id, persons.name AS p_name, machines.name AS m_name, "
                 "mtype.name AS m_type, num_sys.name AS m_system, persons.country AS p_country "
                 "FROM persons "
                 "JOIN pers_mach ON (persons.id=pers_mach.p_id) "
                 "JOIN machines ON (pers_mach.m_id=machines.id) "
                 "JOIN mtype ON (machines.mtype_id=mtype.id) "
                 "JOIN num_sys ON (machines.num_sys_id=num_sys.id)";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();


        // == Insert basic types and systems ==

        // Types
        create = "INSERT INTO mtype (name) "
                 "VALUES "
                 "('Electromechanical'), "
                 "('Automatic Machine'), "
                 "('Mechanical'), "
                 "('Electronic')";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();

        // Number systems
        create = "INSERT INTO num_sys (name) "
                 "VALUES "
                 "('Binary'), "
                 "('Character'), "
                 "('Decimal')";
        // Prepare
        query.prepare(create);
        // Execute
        query.exec();
    }
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

// Create and return type model
QSortFilterProxyModel *Data::getTypeModel(QSqlQueryModel *&typeQueryModel){
    // Initialize Query model
    typeQueryModel = new QSqlQueryModel();

    // Initial data
    typeQueryModel->setQuery("SELECT * FROM mtype", db);

    // Create proxy model for sorting
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(typeQueryModel);

    // Return
    return proxy;
}

// Create and return system model
QSortFilterProxyModel *Data::getSystemModel(QSqlQueryModel *&systemQueryModel){
    // Initialize Query model
    systemQueryModel = new QSqlQueryModel();

    // Initial data
    systemQueryModel->setQuery("SELECT * FROM num_sys", db);

    // Create proxy model for sorting
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(systemQueryModel);

    // Return
    return proxy;
}

