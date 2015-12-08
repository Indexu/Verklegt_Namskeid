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
string getPersonsDB(vector<Person> &p, const char &sortColumn, const bool &desc){

    // Open
    if(db.open()){
        // Empty vector
        p.clear();

        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc || sortColumn == 'd'){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sortColumn =='n'){
            sort = "ORDER BY name "+ orderMethod + ", id " + orderMethod;
        }
        else if(sortColumn == 'd'){
            sort = "ORDER BY id "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'g'){
            sort = "ORDER BY gender "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'c'){
            sort = "ORDER BY country "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'b'){
            sort = "ORDER BY date(date_of_birth) "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'e'){
            sort = "ORDER BY date(date_of_death) "+ orderMethod + ", name " + orderMethod;
        }

        // Query string
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

// Get person row by ID
string getPersonByIdDB(vector<Person> &p, const int &id){

    // Open
    if(db.open()){
        // Empty vector
        p.clear();

        QSqlQuery query(db);

        query.prepare("SELECT * FROM persons "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        if(!query.exec()){
            return query.lastError().text().toStdString();
        }

        string name, gender, dob, dod, country;
        int id;
        if(query.next()){
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
vector<Person> searchPersonDB(const string &searchString, string &message, const string &field, const string &sorting, const bool &desc){
    vector<Person> results; // Result vector

    if(db.open()){
        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sorting == "name"){
            sort = "ORDER BY name "+ orderMethod + ", id " + orderMethod;
        }
        else if(sorting == "" && desc == true){
            sort = "ORDER BY id "+ orderMethod + ", name " + orderMethod;
        }
        else if(sorting != ""){
            sort = "ORDER BY "+ QString::fromStdString(sorting) + " " + orderMethod + ", name " + orderMethod;
        }

        // The query string
        QString queStr = "";

        // QString searchString
        QString ss = QString::fromStdString(searchString);
        // Searches through a specified field
        if(field != ""){
            queStr = "SELECT * FROM persons WHERE " + QString::fromStdString(field) + " LIKE '%'||:ss||'%'";
        }
        // Searches through all the fields
        else{
            queStr ="SELECT * FROM persons WHERE id LIKE '%'||:ss||'%'"
                    "OR id LIKE '%'||:ss||'%'"
                    "OR name LIKE '%'||:ss||'%'"
                    "OR gender LIKE '%'||:ss||'%'"
                    "OR date_of_birth LIKE '%'||:ss||'%'"
                    "OR date_of_death LIKE '%'||:ss||'%'"
                    "OR country LIKE '%'||:ss||'%'";
        }

        // Append sort
        queStr += sort;

        // Query
        query.prepare(queStr);

        // Bind
        query.bindValue(":ss", ss);

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
string getMachinesDB(vector<Machine> &m,  const char &sortColumn, const bool &desc){
    // Open
    if(db.open()){
        // Empty vector
        m.clear();

        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc || sortColumn == 'd'){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sortColumn =='n'){
            sort = "ORDER BY name "+ orderMethod + ", id " + orderMethod;
        }
        else if(sortColumn == 'd'){
            sort = "ORDER BY id "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'y'){
            sort = "ORDER BY year "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 'b'){
            sort = "ORDER BY built "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 't'){
            sort = "ORDER BY type "+ orderMethod + ", name " + orderMethod;
        }
        else if(sortColumn == 's'){
            sort = "ORDER BY system "+ orderMethod + ", name " + orderMethod;
        }

        // The query string
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

// Get machine row by ID
string getMachineByIdDB(vector<Machine> &m, const int &id){

    // Open
    if(db.open()){
        // Empty vector
        m.clear();

        QSqlQuery query(db);

        query.prepare("SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                      "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                      "JOIN mtype ON (machines.mtype_id=mtype.id) "
                      "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        query.exec();

        string name, type, system;
        int id, year;
        bool built;
        if(query.next()){
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
vector<Machine> searchMachineDB(const string &searchString, string &message, const string &field, const string &sorting, const bool &desc){
    vector<Machine> results; // Result vector

    if(db.open()){
        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sorting == "name"){
            sort = "ORDER BY name "+ orderMethod + ", id " + orderMethod;
        }
        else if(sorting == "" && desc == true){
            sort = "ORDER BY id "+ orderMethod + ", name " + orderMethod;
        }
        else if(sorting != ""){
            sort = "ORDER BY "+ QString::fromStdString(sorting) + " " + orderMethod + ", name " + orderMethod;
        }

        // Query string
        QString queStr = "";

        // QString searchString
        QString ss = QString::fromStdString(searchString);

        // Searches through a specified field
        if(field != ""){
            QString qField = QString::fromStdString(field);

            if(field == "name" || field == "id"){
                qField.prepend("machines.");
            }

            queStr = "SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                     "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                     "JOIN mtype ON (machines.mtype_id=mtype.id) "
                     "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                     "WHERE " + qField + " LIKE '%'||:ss||'%'";
        }
        // Searches through all the fields
        else{
            queStr = "SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                     "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                     "JOIN mtype ON (machines.mtype_id=mtype.id) "
                     "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                     "WHERE machines.id LIKE '%'||:ss||'%' "
                     "OR machines.name LIKE '%'||:ss||'%' "
                     "OR year LIKE '%'||:ss||'%' "
                     "OR built LIKE '%'||:ss||'%' "
                     "OR type LIKE '%'||:ss||'%' "
                     "OR system LIKE '%'||:ss||'%'";
        }

        // Add sort
        queStr += sort;

        // Query
        query.prepare(queStr);

        // Bind
        query.bindValue(":ss", ss);

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
string getTSDB(vector<TypeSystem> &ts, const char &table, const char &sortColumn, const bool &desc){

    // Open
    if(db.open()){
        // Empty vector
        ts.clear();

        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc || sortColumn == 'd'){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sortColumn =='n'){
            sort = "ORDER BY name "+ orderMethod + ", id " + orderMethod;
        }
        else if(sortColumn == 'd'){
            sort = "ORDER BY id "+ orderMethod + ", name " + orderMethod;
        }

        // Decide which table
        QString tab = "mtype";

        if(table == 's'){
            tab = "num_sys";
        }

        // Query string
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

// ===== PERSON MACHINE =====
// Get Person Machine
string getPersonMachineDB(vector<PersonMachine> &pm, const char &sortColumn, const bool &desc){

    // Open
    if(db.open()){
        // Empty vector
        pm.clear();

        QSqlQuery query(db);

        // Ascending or descending
        QString orderMethod = "ASC";
        if(desc || sortColumn == 'd'){
            orderMethod = "DESC";
        }

        // Assemble ORDER BY
        QString sort = "";
        if(sortColumn =='p'){
            sort = "ORDER BY p_name "+ orderMethod + ", m_name " + orderMethod;
        }
        else if(sortColumn == 'm'){
            sort = "ORDER BY m_name "+ orderMethod + ", p_name " + orderMethod;
        }
        else if(sortColumn == 'c'){
            sort = "ORDER BY p_country "+ orderMethod + ", p_name " + orderMethod;
        }
        else if(sortColumn == 't'){
            sort = "ORDER BY m_type "+ orderMethod + ", m_name " + orderMethod;
        }
        else if(sortColumn == 's'){
            sort = "ORDER BY m_system "+ orderMethod + ", m_name " + orderMethod;
        }

        // Query string
        QString queStr = "SELECT pers_mach.id AS id, persons.name AS p_name, machines.name AS m_name, "
                         "mtype.name AS m_type, num_sys.name AS m_system, persons.country AS p_country FROM persons "
                         "JOIN pers_mach ON (persons.id=pers_mach.p_id) "
                         "JOIN machines ON (pers_mach.m_id=machines.id) "
                         "JOIN mtype ON (machines.mtype_id=mtype.id) "
                         "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                         + sort;

        // Query
        query.exec(queStr);

        string p_name, p_country, m_name, m_type, m_system;
        int id;
        while(query.next()){
            id = query.value("id").toInt();
            p_name = query.value("p_name").toString().toStdString();
            p_country = query.value("p_country").toString().toStdString();
            m_name = query.value("m_name").toString().toStdString();
            m_type = query.value("m_type").toString().toStdString();
            m_system = query.value("m_system").toString().toStdString();

            PersonMachine temp(id, p_name, p_country, m_name, m_type, m_system);
            pm.push_back(temp);
        }
        // Close
        db.close();

        return "";
    }
    else{
        return "Unable to connect to database";
    }
}

// Add Person Machine connection
string addPersonMachineDB(const int &p_id, const int &m_id){

    string error = "";
    // Check if person exists
    if(personIDExistsDB(p_id, error)){
        // Check if machine exists
        if(machineIDExistsDB(m_id, error)){
            // Check if connection exists
            if(!connectionPMExistsDB(p_id, m_id, error)){
                // Open
                if(db.open()){
                    QSqlQuery query(db);

                    query.prepare("INSERT INTO pers_mach (p_id, m_id) "
                                  "VALUES (:pid, :mid)");

                    query.bindValue(":pid", p_id);
                    query.bindValue(":mid", m_id);

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
                return "exists";
            }
        }
        else if(error != ""){
            return error;
        }
        else{
            return "Machine ID: " + to_string(m_id) + " not found.";
        }
    }
    else if(error != ""){
        return error;
    }
    else{
        return "Person ID: " + to_string(p_id) + " not found.";
    }
}

// Delete person and machine connections
string delPersMachDB(const int &id) {
    string error = "";
    if(persMachConnectionIDExistsDB(id, error)){
        // Open
        if(db.open()){
            QSqlQuery query(db);

            query.prepare("DELETE FROM pers_mach "
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

// Check if machine ID exists in DB
bool persMachConnectionIDExistsDB(const int &id, string &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM pers_mach "
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


// Check if connection exists between person and machine
bool connectionPMExistsDB(const int &pid, const int &mid, string &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM pers_mach "
                      "WHERE p_id = :pid AND m_id = :mid");

        query.bindValue(":pid", pid);
        query.bindValue(":mid", mid);


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

// Get person-machine row by ID
string getPMByIdDB(vector<PersonMachine> &pm, const int &id){

    // Open
    if(db.open()){
        // Empty vector
        pm.clear();

        QSqlQuery query(db);

        query.prepare("SELECT pers_mach.id AS id, persons.name AS p_name, machines.name AS m_name, "
                      "mtype.name AS m_type, num_sys.name AS m_system, persons.country AS p_country FROM persons "
                      "JOIN pers_mach ON (persons.id=pers_mach.p_id) "
                      "JOIN machines ON (pers_mach.m_id=machines.id) "
                      "JOIN mtype ON (machines.mtype_id=mtype.id) "
                      "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                      "WHERE id = :id");

        query.bindValue(":id", id);

        query.exec();

        string p_name, p_country, m_name, m_type, m_system;
        int id;
        if(query.next()){
            id = query.value("id").toInt();
            p_name = query.value("p_name").toString().toStdString();
            p_country = query.value("p_country").toString().toStdString();
            m_name = query.value("m_name").toString().toStdString();
            m_type = query.value("m_type").toString().toStdString();
            m_system = query.value("m_system").toString().toStdString();

            PersonMachine temp(id, p_name, p_country, m_name, m_type, m_system);
            pm.push_back(temp);
        }
        // Close
        db.close();

        return "";
    }
    else{
        return "Unable to connect to database";
    }
}
