#include "domain/services.h"

// Get all machines
bool Services::getAllMachines(QSqlQueryModel *machineQueryModel, QString &error){
    return dataLayer.getAllMachines(machineQueryModel, error);
}

// Search machine
bool Services::searchMachine(QSqlQueryModel *machineQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR name LIKE '%'||:ss||'%' OR year LIKE '%'||:ss||'%' "
                    "OR built LIKE '%'||:ss||'%' OR type LIKE '%'||:ss||'%' OR system LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%'||:ss||'%'";
    }
    // Year
    else if(column == 3){
        filterStr = "year LIKE '%'||:ss||'%'";
    }
    // Built
    else if(column == 4){
        filterStr = "built LIKE '%'||:ss||'%'";
    }
    // Type
    else if(column == 5){
        filterStr = "type LIKE '%'||:ss||'%'";
    }
    // System
    else if(column == 6){
        filterStr = "system LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterMachine(machineQueryModel, filterStr, searchString, error);
}

// Filter machine
bool Services::filterMachine(QSqlQueryModel *machineQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND name NOT LIKE '%'||:ss||'%' "
                    "AND year NOT LIKE '%'||:ss||'%' AND built NOT LIKE '%'||:ss||'%' "
                    "AND type NOT LIKE '%'||:ss||'%' AND system NOT LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%'||:ss||'%'";
    }
    // Year
    else if(column == 3){
        filterStr = "year NOT LIKE '%'||:ss||'%'";
    }
    // Built
    else if(column == 4){
        filterStr = "built NOT LIKE '%'||:ss||'%'";
    }
    // Type
    else if(column == 5){
        filterStr = "type NOT LIKE '%'||:ss||'%'";
    }
    // System
    else if(column == 6){
        filterStr = "system NOT LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterMachine(machineQueryModel, filterStr, searchString, error);
}

// Add machine
bool Services::addMachine(const Machine &m, const int &type_id, const int &sys_id, QString &error){
    return dataLayer.addMachine(m, type_id, sys_id, error);
}

// Delete machine
bool Services::deleteMachine(const QVector<Machine> &m, QString &error){

    for(int i = 0; i < m.size(); i++){
        if(!dataLayer.machineIDExistsDB(m[i].getId(), error)){
            if(error.isEmpty()){
                error = "Machine ID: " + QString::number(m[i].getId()) + " not found.";
            }
            return false;
        }
    }

    return dataLayer.deleteMachine(m, error);
}

// Get machine
bool Services::getMachine(Machine &m, QString &error){
    return dataLayer.getMachine(m, error);
}

// Edit machine
bool Services::editMachine(Machine &m, const int &type_id, const int &sys_id, QString &error){
    return dataLayer.editMachine(m, type_id, sys_id, error);
}

// Get all types or systems
bool Services::getAllTypesSystemsVector(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error){
    return dataLayer.getAllTypesSystemsVector(typeSystems, getTypes, error);
}
