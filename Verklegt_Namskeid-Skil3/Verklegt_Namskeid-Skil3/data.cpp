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
    int id;
    while(query.next()){
        id = query.value("id").toInt();
        name = query.value("name").toString();
        gender = query.value("gender").toString();
        dob = query.value("date_of_birth").toString();
        dod = query.value("date_of_death").toString();
        country = query.value("country").toString();

        Person temp(id, name, gender, dob, dod, country);
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

// Set the filter of personModel
void Data::setFilterPerson(QSqlTableModel *personModel, const QString &filterStr, const QString &searchString, QString &error){
    // Set filter
    personModel->setFilter(filterStr.arg(searchString));

    // Error
    if(personModel->lastError().isValid()){
        error = personModel->lastError().text();
    }
}
