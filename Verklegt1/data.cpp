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

// ===== PERSON =====

// Get data
string getPersonsDB(vector<Person> &p, const string &sorting){

    // Open
    if(db.open()){
        // Empty vector
        p.clear();

        QSqlQuery query(db);

        QString sort = "";
        if(sorting == "a"){
            sort = "ORDER BY name ASC, id ASC";
        }
        else if(sorting == "z"){
            sort = "ORDER BY name DESC, id DESC";
        }
        else if(sorting == "d"){
            sort = "ORDER BY id DESC, name DESC";
        }

        QString queStr = "SELECT * FROM persons " + sort;

        // Query
        query.exec(queStr);

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

// Edit person
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

// Search for a person in DB
vector<Person> searchPersonDB(string &searchString, string &message, string &field){
    vector<Person> results; // Result vector

    if(db.open()){
        QSqlQuery query(db);

        // Check if searching for gender - looks at the first charachter of the search string
        if(field == "gender"){
            if(tolower(searchString[0]) == 'm'){
                query.prepare("SELECT * FROM persons WHERE gender = 'male'");
            }
            else if(tolower(searchString[0]) == 'f'){
                query.prepare("SELECT * FROM persons WHERE gender = 'female'");
            }
            else{
                message = "Unknown gender";
                return results;
            }
        }
        // If not searching for gender it searches either a specifield field, or every field in the table
        else{
            QString ss = QString::fromStdString(searchString);
            // Searches through a specified field
            if(field != ""){
                query.prepare("SELECT * FROM persons WHERE " + QString::fromStdString(field) + " LIKE '%'||:ss||'%'");
                query.bindValue(":ss", ss);
            }
            // Searches through all the fields
            else{
                query.prepare("SELECT * FROM persons WHERE id LIKE '%'||:ss||'%'"
                              "OR id LIKE '%'||:ss||'%'"
                              "OR name LIKE '%'||:ss||'%'"
                              "OR gender LIKE '%'||:ss||'%'"
                              "OR date_of_birth LIKE '%'||:ss||'%'"
                              "OR date_of_death LIKE '%'||:ss||'%'"
                              "OR country LIKE '%'||:ss||'%'");

                query.bindValue(":ss", ss);
            }
        }

        string name, gender, dob, dod, country;
        int id;
        // Execute query
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

// ===== MACHINE =====
// Get data
string getMachinesDB(vector<Machine> &m, const string &sorting){

    // Open
    if(db.open()){
        // Empty vector
        m.clear();

        QSqlQuery query(db);

        QString sort = "";
        if(sorting == "a"){
            sort = "ORDER BY name ASC, id ASC";
        }
        else if(sorting == "z"){
            sort = "ORDER BY name DESC, id DESC";
        }
        else if(sorting == "d"){
            sort = "ORDER BY id DESC, name DESC";
        }

        QString queStr = "SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                         "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                         "JOIN mtype ON (machines.mtype_id=mtype.id) "
                         "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                         + sort;

        // Query
        query.exec(queStr);

        string name, type, system;
        int id, year;
        bool built;
        while(query.next()){
            id = query.value("id").toInt();
            name = query.value("name").toString().toStdString();
            year = query.value("year").toInt();
            built = query.value("built").toBool();
            type = query.value("type").toString().toStdString();
            system = query.value("system").toString().toStdString();

            Machine temp(id, name, year, built, type, system);
            m.push_back(temp);
        }
        // Close
        db.close();

        return "";
    }
    else{
        return "Unable to connect to database";
    }
}

// Search for a machine
vector<Machine> searchMachineDB(string &searchString, string &message, string &field){
    vector<Machine> results; // Result vector

    if(db.open()){
        QSqlQuery query(db);

        QString ss = QString::fromStdString(searchString);
        // Searches through a specified field
        if(field != ""){
            QString qField = QString::fromStdString(field);

            if(field == "name" || field == "id"){
                qField.prepend("machines.");
            }

            query.prepare("SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                          "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                          "JOIN mtype ON (machines.mtype_id=mtype.id) "
                          "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                          "WHERE " + qField + " LIKE '%'||:ss||'%'");

            query.bindValue(":ss", ss);
        }
        // Searches through all the fields
        else{
            query.prepare("SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                          "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                          "JOIN mtype ON (machines.mtype_id=mtype.id) "
                          "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                          "WHERE machines.id LIKE '%'||:ss||'%'"
                          "OR machines.name LIKE '%'||:ss||'%'"
                          "OR year LIKE '%'||:ss||'%'"
                          "OR built LIKE '%'||:ss||'%'"
                          "OR type LIKE '%'||:ss||'%'"
                          "OR system LIKE '%'||:ss||'%'");

            query.bindValue(":ss", ss);
        }
        string name, type, system;
        int id, year;
        bool built;

        if (query.exec()) {
            while(query.next()){
                id = query.value("id").toInt();
                name = query.value("name").toString().toStdString();
                year = query.value("year").toInt();
                built = query.value("built").toBool();
                type = query.value("type").toString().toStdString();
                system = query.value("system").toString().toStdString();

                Machine temp(id, name, year, built, type, system);
                results.push_back(temp);
            }
        }
        else {
            message = query.lastError().text().toStdString();
        }
    }
    else{
        message = "Unable to connect to database";
    }
    db.close();
    return results;
}

// Add Machine
string addMachineDB(const string &name, const string &year, const string &built, const string &type, const string &system){

    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString n = QString::fromStdString(name);
        QString y = QString::fromStdString(year);
        QString b = QString::fromStdString(built);
        QString t = QString::fromStdString(type);
        QString s = QString::fromStdString(system);

        query.prepare("INSERT INTO machines (name, year, built, mtype_id, num_sys_id) "
                      "VALUES (:name, :year, :build, :mtype, :num_sys)");

        query.bindValue(":name", n);
        query.bindValue(":year", y);
        query.bindValue(":build", b);
        query.bindValue(":mtype", t);
        query.bindValue(":num_sys", s);

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

// Delete machine
string delMachineDB(const int &id){
    string error = "";
    if(machineIDExistsDB(id, error)){
        // Open
        if(db.open()){
            QSqlQuery query(db);

            query.prepare("DELETE FROM machines "
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

// Edit machine
string editMachineDB(const int &id, const string &column, const string &value){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString col = QString::fromStdString(column);

        QString queStr = "UPDATE machines ";
        queStr.append("SET " + col + " = :val WHERE id = :id");

        query.prepare(queStr);


        QString val = QString::fromStdString(value);

        //query.bindValue(":col", col);
        query.bindValue(":val", val);
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

// Check if machine ID exists in DB
bool machineIDExistsDB(const int &id, string &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM machines "
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

// ===== Types and Systems =====
// Get data
string getTSDB(vector<TypeSystem> &ts, const string &table, const string &sorting){

    // Open
    if(db.open()){
        // Empty vector
        ts.clear();

        QSqlQuery query(db);

        QString sort = "";
        if(sorting == "a"){
            sort = "ORDER BY name ASC, id ASC";
        }
        else if(sorting == "z"){
            sort = "ORDER BY name DESC, id DESC";
        }
        else if(sorting == "d"){
            sort = "ORDER BY id DESC, name DESC";
        }

        QString tab = QString::fromStdString(table);

        QString queStr = "SELECT * FROM " + tab + " "
                         + sort;

        // Query
        query.exec(queStr);

        string name;
        int id;
        while(query.next()){
            id = query.value("id").toInt();
            name = query.value("name").toString().toStdString();

            TypeSystem temp(id, name);
            ts.push_back(temp);
        }
        // Close
        db.close();

        return "";
    }
    else{
        return "Unable to connect to database";
    }
}
