#include "data/data.h"

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

// Delete connection
bool Data::deleteConnection(const QVector<PersonMachine> &pm, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        // Start of delete from machines query
        QString queStr = "DELETE FROM pers_mach "
                 "WHERE id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < pm.size(); i++){
            queStr += QString::number(pm[i].getId());

            if((i+1) != pm.size()){
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

// Filter connection
bool Data::filterConnection(QSqlQueryModel *connectionQueryModel, const QString &filterStr, const QString &searchString, QString &error){
    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM pers_machView "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        connectionQueryModel->setQuery(query);

        // Model Error
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

// Get Connection
bool Data::getConnection(PersonMachine &pm, QString error){
    if (db.open()){
        int id = pm.getId();

        QSqlQuery query(db);
        query.prepare("SELECT * FROM pers_machView "
                      "WHERE id = :id");

        query.bindValue(":id",id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        QString p_name, m_name, m_type, m_system, p_country;
        if (query.next()) {
            p_name = query.value("p_name").toString();
            m_name = query.value("m_name").toString();
            m_type = query.value("m_type").toString();
            m_system = query.value("m_system").toString();
            p_country = query.value("p_country").toString();

            pm.setP_Name(p_name);
            pm.setM_Name(m_name);
            pm.setM_Type(m_type);
            pm.setM_System(m_system);
            pm.setP_Country(p_country);
        }
        else{
            error = "No connection, id: " + QString::number(pm.getId());
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

// Check if pers_mach ID exists
bool Data::connectionIDExistsDB(const int &id, QString &error){
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM pers_mach "
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
