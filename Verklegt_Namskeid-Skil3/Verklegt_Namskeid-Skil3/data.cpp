#include "data.h"

// Constructor
Data::Data(){

}

// Deconstructor
Data::~Data(){
    QSqlDatabase db = getDBCon();
    db.close();
}

// Get database connection
QSqlDatabase Data::getDBCon(){

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

    return db;
}

// Get data
QVector<Person> Data::getPersons(){
    // DB con
    QSqlDatabase db = getDBCon();

    QVector<Person> p;

    if(!db.isOpen()){
        db.open();
    }

    QSqlQuery query(db);

    // Query string
    QString queStr = "SELECT * FROM persons";

    qDebug() << "PATH: " << QDir::currentPath();

    query.prepare(queStr);

    // Query
    if(!query.exec()){
        qDebug() << query.executedQuery();
        qDebug() << query.lastError().text();
    }

    QString name, gender, dob, dod, country;
    while(query.next()){
        name = query.value("name").toString();
        gender = query.value("gender").toString();
        dob = query.value("date_of_birth").toString();
        dod = query.value("date_of_death").toString();
        country = query.value("country").toString();

        Person temp(name, gender, dob, dod, country);
        p.push_back(temp);
    }
    // Close
    db.close();

    return p;
}

// Create and return person model
QSortFilterProxyModel *Data::getPersonModel(QSqlQueryModel *&personQueryModel){
    // Database connection
    QSqlDatabase db = getDBCon();

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
    // Database connection
    QSqlDatabase db = getDBCon();

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
    // Database connection
    QSqlDatabase db = getDBCon();

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
    // Database connection
    QSqlDatabase db = getDBCon();

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
    QSqlDatabase db = getDBCon();

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
    // DB con
    QSqlDatabase db = getDBCon();

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
bool Data::deletePerson(const int &id, QString &error){
    // DB con
    QSqlDatabase db = getDBCon();

    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("DELETE FROM persons "
                      "WHERE id = :id");

        query.bindValue(":id", id);

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
        return false;
    }
}

// Edit person
bool Data::editPerson(const Person &p, QString &error){
    // DB con
    QSqlDatabase db = getDBCon();

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
// DB con
    QSqlDatabase db = getDBCon();

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
    QSqlDatabase db = getDBCon();
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
            qDebug() << "No person, id: " << p.getId();
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
    // Database connection
    QSqlDatabase db = getDBCon();

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
