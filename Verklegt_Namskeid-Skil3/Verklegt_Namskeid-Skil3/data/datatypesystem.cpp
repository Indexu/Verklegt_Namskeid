#include "data/data.h"

// Get all types
bool Data::getAllTypes(QSqlQueryModel *typeQueryModel, QString &error){
    if(db.open()){
        // Connect model to table
        typeQueryModel->setQuery("SELECT * FROM mtype", db);

        if(typeQueryModel->lastError().isValid()){
            error = typeQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Get all systems
bool Data::getAllSystems(QSqlQueryModel *systemQueryModel, QString &error){
    if(db.open()){
        // Connect model to table
        systemQueryModel->setQuery("SELECT * FROM num_sys", db);

        if(systemQueryModel->lastError().isValid()){
            error = systemQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }
    return false;
}

// Set filter of type
bool Data::filterType(QSqlQueryModel *typeQueryModel, const QString &filterStr, const QString &searchString, QString &error){
    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM mtype "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        typeQueryModel->setQuery(query);

        // Model Error
        if(typeQueryModel->lastError().isValid()){
            error = typeQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Set filter of system
bool Data::filterSystem(QSqlQueryModel *systemQueryModel, const QString &filterStr, const QString &searchString, QString &error){
    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM num_sys "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        systemQueryModel->setQuery(query);

        // Model Error
        if(systemQueryModel->lastError().isValid()){
            error = systemQueryModel->lastError().text();
            return false;
        }

        return true;
    }
    else{
        error = "Unable to connect to database";
    }

    return false;
}

// Add type / system
bool Data::addTypeSystem(const QString &ts, const bool &type, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString queStr = "";
        if(type){
            queStr = "INSERT INTO mtype (name) "
                     "VALUES (:name)";
        }
        else{
            queStr = "INSERT INTO num_sys (name) "
                     "VALUES (:name)";
        }

        query.prepare(queStr);

        query.bindValue(":name", ts);

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

// Delete type / system
bool Data::deleteTypeSystem(const QVector<TypeSystem> &ts, const bool &type, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString queStr = "";

        // Start of delete in machines table
        if(type){
            queStr = "DELETE FROM machines "
                     "WHERE mtype_id IN (";
        }
        else{
            queStr = "DELETE FROM machines "
                     "WHERE num_sys_id IN (";
        }

        // Add IDs to be deleted to query
        for(int i = 0; i < ts.size(); i++){
            queStr += QString::number(ts[i].getId());

            if((i+1) != ts.size()){
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

        // Start of delete from corresponding table query
        if(type){
            queStr = "DELETE FROM mtype "
                     "WHERE id IN (";
        }
        else{
            queStr = "DELETE FROM num_sys "
                     "WHERE id IN (";
        }

        // Add IDs to be deleted to query
        for(int i = 0; i < ts.size(); i++){
            queStr += QString::number(ts[i].getId());

            if((i+1) != ts.size()){
                queStr += ", ";
            }
        }

        // Close delete
        queStr += ")";

        // Prepare delete
        query.prepare(queStr);

        // Execute delete
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

// Get type / system
bool Data::getTypeSystem(TypeSystem &ts, const bool &type, QString &error){
    if (db.open()){
        QSqlQuery query(db);

        int id = ts.getId();

        QString queStr = "";

        if(type){
            queStr = "SELECT * FROM mtype "
                     "WHERE id = :id";
        }
        else{
            queStr = "SELECT * FROM num_sys "
                     "WHERE id = :id";
        }

        query.prepare(queStr);

        query.bindValue(":id",id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        QString name;

        if (query.next()) {
            name = query.value("name").toString();

            ts.setName(name);
        }
        else{
            if(type){
                error = "Type ID: " + QString::number(ts.getId()) + " not found.";
            }
            else{
                error = "System ID: " + QString::number(ts.getId()) + " not found.";
            }
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

// Edit type / system
bool Data::editTypeSystem(const TypeSystem &ts, const bool &type, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        QString queStr = "";

        if(type){
            queStr = "UPDATE mtype "
                     "SET name = :name "
                     "WHERE id = :id";
        }
        else{
            queStr = "UPDATE num_sys "
                     "SET name = :name "
                     "WHERE id = :id";
        }

        query.prepare(queStr);

        query.bindValue(":id", ts.getId());
        query.bindValue(":name", ts.getName());

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

// Check if type / system ID exists
bool Data::typeSystemIDExistsDB(const int &id, const bool &type, QString &error){
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        QString queStr = "";

        if(type){
            queStr = "SELECT id FROM mtype "
                     "WHERE id = :id";
        }
        else{
            queStr = "SELECT id FROM num_sys "
                     "WHERE id = :id";
        }

        query.prepare(queStr);

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
bool Data::getAllTypesSystemsVector(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error){
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
