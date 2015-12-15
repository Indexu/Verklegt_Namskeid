#include "data/data.h"

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
            error = "Person ID: " + QString::number(p.getId()) + " not found.";
            return false;
        }

        db.close();

        return true;
    }
    else{
        error = "Unable to connect to database";
        return false;
    }
}
