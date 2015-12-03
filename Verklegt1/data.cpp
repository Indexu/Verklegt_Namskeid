#include "data.h"
#include "QtSql"

using namespace std;

// Get data
void getData(vector<Person> &p, string &message){
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "verklegt.sqlite";
    db.setDatabaseName(dbName);
    // Open
    db.open();

    QSqlQuery query(db);
    // Query
    query.exec("SELECT * FROM persons");

    string name, gender, dob, dod, country;
    int id;
    while(query.next()){
        id = query.value("id").toInt();
        name = query.value("name").toString().toStdString();
        gender = query.value("gender").toString().toStdString();
        dob = query.value("date_of_birth").toString().toStdString();
        dod = query.value("date_of_death").toString().toStdString();
        country = query.value("country").toString().toStdString();

        Person temp(id, name, gender, dob, dod, country);
        p.push_back(temp);
    }
    // Close
    db.close();

}

// Add Person
void addPersonDB(const string &name, const string &gender, const string &dob, const string &dod, const string &country){
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "verklegt.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    QString n = QString::fromStdString(name);
    QString g = QString::fromStdString(gender);
    QString b = QString::fromStdString(dob);
    QString d = QString::fromStdString(dod);
    QString c = QString::fromStdString(country);

    query.prepare("INSERT INTO persons (name, gender, date_of_birth, date_of_death, country) "
                  "VALUES (:name, :gender, :dob, :dod, :country)");

    query.bindValue(":name", n);
    query.bindValue(":gender", g);
    query.bindValue(":dob", b);
    query.bindValue(":dod", d);
    query.bindValue(":country", c);

    query.exec();

    db.close();
}
