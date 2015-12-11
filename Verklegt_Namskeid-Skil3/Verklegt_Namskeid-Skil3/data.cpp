#include "data.h"

// Constructor
Data::Data(){

}

// Deconstructor
Data::~Data(){
    QSqlDatabase db = Data::getDBCon();
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
    QSqlDatabase db = Data::getDBCon();

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
QSqlTableModel* Data::getPersonModel(QObject *parent){
    // Database connection
    QSqlDatabase db = Data::getDBCon();

    // Connect model to DB
    QSqlTableModel *model = new QSqlTableModel(parent, db);

    // Connect model to table
    model->setTable(constants::TABLE_PERSON);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    // Return
    return model;
}

// Create and return machine model
QSqlTableModel *Data::getMachineModel(QObject *parent){
    // Database connection
    QSqlDatabase db = Data::getDBCon();

    // Connect model to DB
    QSqlTableModel *model = new QSqlTableModel(parent, db);

    // Connect model to table
    model->setTable(constants::TABLE_MACHINE);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    // Return
    return model;
}

// Create and return connection model
QSqlTableModel *Data::getConnectionModel(QObject *parent){
    // Database connection
    QSqlDatabase db = Data::getDBCon();

    // Connect model to DB
    QSqlTableModel *model = new QSqlTableModel(parent, db);

    // Connect model to table
    model->setTable(constants::TABLE_CONNECTIONS);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    // Return
    return model;
}

bool Data::getAllPersons(QSqlTableModel *personModel, QString &error){
    // Database connection
    QSqlDatabase db = Data::getDBCon();

    if(db.open()){
        // Connect model to table
        personModel->setFilter("");

        if(personModel->select()){
            return true;
        }
        else{
            error = "Unable to access table";
        }
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Set the filter of personModel
void Data::setFilterPerson(QSqlTableModel *personModel, const QString &filterStr, const QString &searchString, QString &error){
    // Set filter
    personModel->setFilter(filterStr.arg(searchString));

    // Error
    if(personModel->lastError().isValid()){
        error = personModel->lastError().text();
    }
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

            qDebug() << p.getCountry();
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
