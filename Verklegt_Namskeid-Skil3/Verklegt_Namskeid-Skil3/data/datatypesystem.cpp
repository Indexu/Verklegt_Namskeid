#include "data/data.h"

// Get all names from types or systems
bool Data::getAllTypesSystems(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error){
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
