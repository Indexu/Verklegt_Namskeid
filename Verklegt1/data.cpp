#include "data.h"
#include "QtSql"

using namespace std;

const QString DB_NAME = "verklegt.sqlite";
QSqlDatabase db;

// Initialize database connection
string initDB(){

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = DB_NAME;
    db.setDatabaseName(dbName);

    if(!db.open()){
        return "Unable to connect to database";
    }
    else{
        return "";
    }
}

// Get data
string getData(vector<Person> &p){

    // Open
    if(db.open()){
        // Empty vector
        p.clear();

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

        return "";
    }
    else{
        return "Unable to connect to database";
    }
}

// Add Person
string addPersonDB(const string &name, const string &gender, const string &dob, const string &dod, const string &country){

    // Open
    if(db.open()){
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

        if(!query.exec()){
            return query.lastError().text().toStdString();
        }

        // Close
        db.close();
        return "";
    }
    else{
        return "Unable to connect to database";
    }

}

// Delete person
string delPersonDB(const int &id){
    string error = "";
    if(personIDExistsDB(id, error)){
        // Open
        if(db.open()){
            QSqlQuery query(db);

            query.prepare("DELETE FROM persons "
                          "WHERE id = :id");

            query.bindValue(":id", id);

            if(!query.exec()){
                return query.lastError().text().toStdString();
            }

            // Close
            db.close();
            return "";
        }
        else{
            return "Unable to connect to database";
        }
    }
    else if(error != ""){
        return error;
    }
    else{
        return "ID: " + to_string(id) + " not found.";
    }
}

string editPersonDB(const int &id, const string &column, const string &value){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString col = QString::fromStdString(column);

        QString queStr = "UPDATE persons ";
        queStr.append("SET " + col + " = :val WHERE id = :id");

        query.prepare(queStr);


        QString val = QString::fromStdString(value);

        //query.bindValue(":col", col);
        query.bindValue(":val", val);
        query.bindValue(":id", id);

        cout << query.lastQuery().toStdString() << endl;

        if(!query.exec()){
            return query.lastError().text().toStdString();
        }

        // Close
        db.close();
        return "";
    }
    else{
        return "Unable to connect to database";
    }
}

// Check if person ID exists in DB
bool personIDExistsDB(const int &id, string &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM persons "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        if(!query.exec()){
            error = query.lastError().text().toStdString();
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

vector<Person> searchPersonDB(string &searchString, string &message, string &field){
    vector<Person> results; // Result vector

    if(db.open()){
        QSqlQuery query(db);
        QString ss = QString::fromStdString(searchString);

        query.prepare("SELECT * FROM persons WHERE " + QString::fromStdString(field) + " LIKE '%'||:ss||'%'");

        query.bindValue(":ss", ss);

        string name, gender, dob, dod, country;
        int id;

        if (query.exec()) {
            while(query.next()){
                id = query.value("id").toInt();
                name = query.value("name").toString().toStdString();
                gender = query.value("gender").toString().toStdString();
                dob = query.value("date_of_birth").toString().toStdString();
                dod = query.value("date_of_death").toString().toStdString();
                country = query.value("country").toString().toStdString();

                Person temp(id, name, gender, dob, dod, country);
                results.push_back(temp);
            }
        }
        else {
            message = query.lastError().text().toStdString();;
        }
    }
    else{
        message = "Unable to connect to database";
    }
    db.close();
    return results;
}
