#include "data/data.h"

// Get all machines
bool Data::getAllMachines(QSqlQueryModel *machineQueryModel, QString &error){
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

// Filter machine
bool Data::filterMachine(QSqlQueryModel *machineQueryModel, const QString &filterStr, const QString &searchString, QString &error){
    if(db.open()){
        QSqlQuery query(db);

        // Prepare
        query.prepare("SELECT * FROM machinesView "
                      "WHERE " + filterStr);
        // Bind
        query.bindValue(":ss", searchString);

        // Query error
        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        // Set Query
        machineQueryModel->setQuery(query);

        // Model Error
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

// Add machine
bool Data::addMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("INSERT INTO machines (name, year, built, mtype_id, num_sys_id) "
                          "VALUES (:name, :year, :built, :mtype_id, :num_sys_id)");

        query.bindValue(":name", m.getName());

        // Check year
        if(m.getYear() == 0){
            query.bindValue(":year", "-");
        }
        else{
            query.bindValue(":year", m.getYear());
        }

        query.bindValue(":built", m.getBuilt());
        query.bindValue(":mtype_id", type_id);
        query.bindValue(":num_sys_id", sys_id);

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

// Delete machines
bool Data::deleteMachine(const QVector<Machine> &m, QString &error){
    // Open
    if(db.open()){
        QSqlQuery query(db);

        // Start of delete from connections query
        QString queStr = "DELETE FROM pers_mach "
                         "WHERE m_id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < m.size(); i++){
            queStr += QString::number(m[i].getId());

            if((i+1) != m.size()){
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

        // Start of delete from machines query
        queStr = "DELETE FROM machines "
                 "WHERE id IN (";

        // Add IDs to be deleted to query
        for(int i = 0; i < m.size(); i++){
            queStr += QString::number(m[i].getId());

            if((i+1) != m.size()){
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

// Get machine
bool Data::getMachine(Machine &m, QString &error){
    if (db.open()){
        int id = m.getId();

        QSqlQuery query(db);
        query.prepare("SELECT machines.id AS id, machines.name AS name, machines.year AS year, "
                      "machines.built AS built, mtype.name AS type, num_sys.name AS system FROM machines "
                      "JOIN mtype ON (machines.mtype_id=mtype.id) "
                      "JOIN num_sys ON (machines.num_sys_id=num_sys.id) "
                      "WHERE machines.id = :id");

        query.bindValue(":id",id);

        if(!query.exec()){
            error = query.lastError().text();
            return false;
        }

        QString name, type, system;
        int year;
        bool built;
        if (query.next()) {
            name = query.value("name").toString();
            year = query.value("year").toInt();
            built = query.value("built").toBool();
            type = query.value("type").toString();
            system = query.value("system").toString();

            m.setName(name);
            m.setYear(year);
            m.setBuilt(built);
            m.setType(type);
            m.setSystem(system);
        }
        else{
            error = "Machine ID: " + QString::number(m.getId()) + " not found.";
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
// Edit machine
bool Data::editMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error){

    // Open
    if(db.open()){
        QSqlQuery query(db);

        query.prepare("UPDATE machines "
                      "SET name = :name, "
                      "year = :year, "
                      "built = :built, "
                      "mtype_id = :mtype_id, "
                      "num_sys_id = :num_sys_id "
                      "WHERE id = :id");

        query.bindValue(":id", m.getId());
        query.bindValue(":name", m.getName());
        // Check year
        if (m.getYear() == 0){
            query.bindValue(":year", "-");
        }
        else{
            query.bindValue(":year", m.getYear());
        }
        query.bindValue(":built", m.getBuilt());
        query.bindValue(":mtype_id", type_id);
        query.bindValue(":num_sys_id", sys_id);

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


// Check if machine ID exists
bool Data::machineIDExistsDB(const int &id, QString &error){
    // Open
    if(db.open()){
        bool exists = false;
        QSqlQuery query(db);

        query.prepare("SELECT id FROM machines "
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
