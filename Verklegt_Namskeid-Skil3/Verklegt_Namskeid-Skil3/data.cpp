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

// Get all persons
bool Data::getAllPersons(QSqlQueryModel *personQueryModel, QString &error){

    if(db.open()){
        // Connect model to table
        personQueryModel->setQuery("SELECT * FROM persons", db);

        if(personQueryModel->lastError().isValid()){
            error = personQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Set the filter of personModel
bool Data::filterPerson(QSqlQueryModel *personQueryModel, const QString &filterStr, const QString &searchString, QString &error){

    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM persons "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        personQueryModel->setQuery(query);

        // Model Error
        if(personQueryModel->lastError().isValid()){
            error = personQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Add person
bool Data::addPerson(const Person &p, QString &error){

    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("INSERT INTO persons (name, gender, date_of_birth, date_of_death, country) "
                          "VALUES (:name, :gender, :dob, :dod, :country)");

        query.bindValue(":name", p.getName());
        query.bindValue(":gender", p.getGender());
        query.bindValue(":dob", p.getDateOfBirth());
        query.bindValue(":dod", p.getDateOfDeath());
        query.bindValue(":country", p.getCountry());

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Delete person
bool Data::deletePerson(const QVector<Person> &p, QString &error){

    // Open
    if(db.open()){
        QSqlQuery query(db);

        // Start of delete from connections query
        QString queStr = "DELETE FROM pers_mach "
                         "WHERE p_id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < p.size(); i++){
            queStr += QString::number(p[i].getId());

            if((i+1) != p.size()){
                queStr += ", ";
            }
        }

        // Close delete from connections query
        queStr += ")";

        // Prepare delete from connections
        query.prepare(queStr);

        // Execute delete from connections
        if(!query.exec()){
            error = query.executedQuery();
            return false;
        }

        // Start of delete from persons query
        queStr = "DELETE FROM persons "
                         "WHERE id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < p.size(); i++){
            queStr += QString::number(p[i].getId());

            if((i+1) != p.size()){
                queStr += ", ";
            }
        }

        // Close delete from persons query
        queStr += ")";

        // Prepare delete from persons
        query.prepare(queStr);

        // Execute delete from persons
        if(!query.exec()){
            error = query.executedQuery();
            return false;
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
        return false;
    }
}

// Edit person
bool Data::editPerson(const Person &p, QString &error){

    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("UPDATE persons "
                      "SET name = :name, "
                      "gender = :gender, "
                      "date_of_birth = :dob, "
                      "date_of_death = :dod, "
                      "country = :country "
                      "WHERE id = :id");

        query.bindValue(":id", p.getId());
        query.bindValue(":name", p.getName());
        query.bindValue(":gender", p.getGender());
        query.bindValue(":dob", p.getDateOfBirth());
        query.bindValue(":dod", p.getDateOfDeath());
        query.bindValue(":country", p.getCountry());

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }
        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Check if person ID exists
bool Data::personIDExistsDB(const int &id, QString &error){

    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM persons "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        if(!query.exec()){
            error = query.lastError().text();
        }
        else if(query.next()){
             exists = true;
        }

        // Close
        db.close();
        return exists;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Get person by ID
bool Data::getPerson(Person &p, QString &error){

    if (db.open()){
        int id = p.getId();

        QSqlQuery query(db);
        query.prepare("SELECT * FROM persons "
                      "WHERE id = :id");
        query.bindValue(":id",id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        QString name, gender, dob, dod, country;

        if (query.next()) {
            name = query.value("name").toString();
            gender = query.value("gender").toString();
            dob = query.value("date_of_birth").toString();
            dod = query.value("date_of_death").toString();
            country = query.value("country").toString();

            p.setName(name);
            p.setGender(gender);
            p.setDateOfBirth(dob);
            p.setDateOfDeath(dod);
            p.setCountry(country);
        }
        else{
            error = "No person, id: " + QString::number(p.getId());
        }

        db.close();
        
        return true;
    }
    else{
        error = "Unable to connect to database";
        return false;
    }
    return false;
}

// ==== Machines ====
// Get all machines
bool Data::getAllMachines(QSqlQueryModel *machineQueryModel, QString &error){
    if(db.open()){
        // Connect model to table
        machineQueryModel->setQuery("SELECT * FROM machinesView", db);

        if(machineQueryModel->lastError().isValid()){
            error = machineQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Filter machine
bool Data::filterMachine(QSqlQueryModel *machineQueryModel, const QString &filterStr, const QString &searchString, QString &error){
    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM machinesView "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        machineQueryModel->setQuery(query);

        // Model Error
        if(machineQueryModel->lastError().isValid()){
            error = machineQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Add machine
bool Data::addMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("INSERT INTO machines (name, year, built, mtype_id, num_sys_id) "
                          "VALUES (:name, :year, :built, :mtype_id, :num_sys_id)");

        query.bindValue(":name", m.getName());

        // Check year
        if(m.getYear() == 0){
            query.bindValue(":year", "");
        }
        else{
            query.bindValue(":year", m.getYear());
        }

        query.bindValue(":built", m.getBuilt());
        query.bindValue(":mtype_id", type_id);
        query.bindValue(":num_sys_id", sys_id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Delete machines
bool Data::deleteMachine(const QVector<Machine> &m, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        // Start of delete from connections query
        QString queStr = "DELETE FROM pers_mach "
                         "WHERE m_id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < m.size(); i++){
            queStr += QString::number(m[i].getId());

            if((i+1) != m.size()){
                queStr += ", ";
            }
        }

        // Close delete from connections query
        queStr += ")";

        // Prepare delete from connections
        query.prepare(queStr);

        // Execute delete from connections
        if(!query.exec()){
            error = query.executedQuery();
            return false;
        }

        // Start of delete from machines query
        queStr = "DELETE FROM machines "
                 "WHERE id IN (";

        // Add IDs to be machines to query
        for(int i = 0; i < m.size(); i++){
            queStr += QString::number(m[i].getId());

            if((i+1) != m.size()){
                queStr += ", ";
            }
        }

        // Close delete from machines query
        queStr += ")";

        // Prepare delete from machines
        query.prepare(queStr);

        // Execute delete from machines
        if(!query.exec()){
            error = query.executedQuery();
            return false;
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
        return false;
    }
}

// Get machine
bool Data::getMachine(Machine &m, QString &error){
    if (db.open()){
        int id = m.getId();

        QSqlQuery query(db);
        query.prepare("SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                      "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                      "JOIN mtype ON (machines.mtype_id=mtype.id) "
                      "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                      "WHERE machines.id = :id");

        query.bindValue(":id",id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        QString name, type, system;
        int year;
        bool built;
        if (query.next()) {
            name = query.value("name").toString();
            year = query.value("year").toInt();
            built = query.value("built").toBool();
            type = query.value("type").toString();
            system = query.value("system").toString();

            m.setName(name);
            m.setYear(year);
            m.setBuilt(built);
            m.setType(type);
            m.setSystem(system);
        }
        else{
            error = "No person, id: " + QString::number(m.getId());
        }

        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
        return false;
    }
    return false;
}

// Check if machine ID exists
bool Data::machineIDExistsDB(const int &id, QString &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM machines "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        if(!query.exec()){
            error = query.lastError().text();
        }
        else if(query.next()){
             exists = true;
        }

        // Close
        db.close();
        return exists;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Get all names from types or systems
bool Data::getAllTypesSystems(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error){
    // Open
    if(db.open()){
        // Empty vector
        typeSystems.clear();

        QSqlQuery query(db);

        // Query string
        QString queStr = "";

        // Which table to select from
        if(getTypes){
            queStr = "SELECT * FROM mtype";
        }
        else{
            queStr = "SELECT * FROM num_sys";
        }

        // Query
        query.exec(queStr);

        // Error
        if(query.lastError().isValid()){
            error = query.lastError().text();
            return false;
        }

        // Get values in vector
        QString name;
        int id;
        while(query.next()){
            id = query.value("id").toInt();
            name = query.value("name").toString();

            TypeSystem temp(id, name);

            typeSystems.push_back(temp);
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// ==== Connections ====
// Get all connections
bool Data::getAllConnections(QSqlQueryModel *connectionQueryModel, QString &error){
    if(db.open()){
        // Connect model to table
        connectionQueryModel->setQuery("SELECT * FROM pers_machView", db);

        if(connectionQueryModel->lastError().isValid()){
            error = connectionQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Add connection
bool Data::addConnection(const int &p_id, const int &m_id, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("INSERT INTO pers_mach (p_id, m_id) "
                      "VALUES (:pid, :mid)");

        query.bindValue(":pid", p_id);
        query.bindValue(":mid", m_id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Close
        db.close();
        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Check if connection between Person and Machine exists
bool Data::connectionExists(const int &p_id, const int &m_id, QString &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM pers_mach "
                      "WHERE p_id = :pid AND m_id = :mid");

        query.bindValue(":pid", p_id);
        query.bindValue(":mid", m_id);


        if(!query.exec()){
            error = query.lastError().text();
        }
        else if(query.next()){
             exists = true;
        }

        // Close
        db.close();
        return exists;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}
