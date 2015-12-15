#include "services.h"

// Constructor
Services::Services(){

}

// ===== MODELS =====
// Get person model from data layer
QSortFilterProxyModel *Services::getPersonModel(QSqlQueryModel *&personQueryModel){
    return dataLayer.getPersonModel(personQueryModel);
}
// Get machine model from data layer
QSortFilterProxyModel *Services::getMachineModel(QSqlQueryModel *&machineQueryModel){
    return dataLayer.getMachineModel(machineQueryModel);
}
// Get connection model from data layer
QSortFilterProxyModel *Services::getConnectionModel(QSqlQueryModel *&connectionQueryModel){
    return dataLayer.getConnectionModel(connectionQueryModel);
}

// Get all persons
bool Services::getAllPersons(QSqlQueryModel *personQueryModel, QString &error){
    return dataLayer.getAllPersons(personQueryModel, error);
}

// Search for a person
bool Services::searchPerson(QSqlQueryModel *personQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR name LIKE '%'||:ss||'%' OR gender LIKE '%'||:ss||'%' "
                    "OR date_of_birth LIKE '%'||:ss||'%' OR date_of_death LIKE '%'||:ss||'%' "
                    "OR country LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%'||:ss||'%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender LIKE '%'||:ss||'%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth LIKE '%'||:ss||'%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death LIKE '%'||:ss||'%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterPerson(personQueryModel, filterStr, searchString, error);
}

// Filter person
bool Services::filterPerson(QSqlQueryModel *personQueryModel, const QString &searchString, const int &column, QString &error)
{
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND name NOT LIKE '%'||:ss||'%' "
                    "AND gender NOT LIKE '%'||:ss||'%' AND date_of_birth NOT LIKE '%'||:ss||'%' "
                    "AND date_of_death NOT LIKE '%'||:ss||'%' AND country NOT LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%'||:ss||'%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender NOT LIKE '%'||:ss||'%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth NOT LIKE '%'||:ss||'%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death NOT LIKE '%'||:ss||'%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country NOT LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterPerson(personQueryModel, filterStr, searchString, error);
}

// Add person
bool Services::addPerson(const Person &p, QString &error){
    return dataLayer.addPerson(p, error);
}

// Delete person
bool Services::deletePerson(const QVector<Person> &p, QString &error){

    for(int i = 0; i < p.size(); i++){
        if(!dataLayer.personIDExistsDB(p[i].getId(), error)){
            if(error.isEmpty()){
                error = "Person ID: " + QString::number(p[i].getId()) + " not found.";
            }
            return false;
        }
    }

    return dataLayer.deletePerson(p, error);
}

// Get person, by ID stored in &p
bool Services::getPerson(Person &p, QString &error){
    return dataLayer.getPerson(p, error);
}

// Edit person
bool Services::editPerson(const Person &p, QString &error){
    return dataLayer.editPerson(p, error);
}

// ==== Machines ====
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
bool Services::getAllTypesSystems(QVector<TypeSystem> &typeSystems, const bool &getTypes, QString &error){
    return dataLayer.getAllTypesSystems(typeSystems, getTypes, error);
}

// ==== CONNECTIONS ====
// Get all connections
bool Services::getAllConnections(QSqlQueryModel *connectionQueryModel, QString &error){
    return dataLayer.getAllConnections(connectionQueryModel, error);
}

// Add connection
bool Services::addConnection(const int &p_id, const int &m_id, QString &error){
    if(!dataLayer.personIDExistsDB(p_id, error)){
        error = "Person ID: " + QString::number(p_id) + " not found.";
        return false;
    }
    else if(!dataLayer.machineIDExistsDB(m_id, error)){
        error = "Machine ID: " + QString::number(m_id) + " not found.";
        return false;
    }
    else if(dataLayer.connectionExists(p_id, m_id, error)){
        error = "Connection already exists!";
        return false;
    }

    return dataLayer.addConnection(p_id, m_id, error);
}

// Delete connection
bool Services::deleteConnection(const QVector<PersonMachine> &pm, QString &error){
    for(int i = 0; i < pm.size(); i++){
        if(!dataLayer.connectionIDExistsDB(pm[i].getId(), error)){
            if(error.isEmpty()){
                error = "Connection ID: " + QString::number(pm[i].getId()) + " not found.";
            }
            return false;
        }
    }

    return dataLayer.deleteConnection(pm, error);
}

// Search connections
bool Services::searchConnection(QSqlQueryModel *connectionQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR p_name LIKE '%'||:ss||'%' "
                    "OR m_name LIKE '%'||:ss||'%' OR m_type LIKE '%'||:ss||'%' "
                    "OR m_system LIKE '%'||:ss||'%' OR p_country LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "p_name LIKE '%'||:ss||'%'";
    }
    // Year
    else if(column == 3){
        filterStr = "m_name LIKE '%'||:ss||'%'";
    }
    // Built
    else if(column == 4){
        filterStr = "m_type LIKE '%'||:ss||'%'";
    }
    // Type
    else if(column == 5){
        filterStr = "m_system LIKE '%'||:ss||'%'";
    }
    // System
    else if(column == 6){
        filterStr = "p_country LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterConnection(connectionQueryModel, filterStr, searchString, error);
}

// Filter connections
bool Services::filterConnection(QSqlQueryModel *connectionQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND p_name NOT LIKE '%'||:ss||'%' "
                    "AND m_name NOT LIKE '%'||:ss||'%' AND m_type NOT LIKE '%'||:ss||'%' "
                    "AND m_system NOT LIKE '%'||:ss||'%' AND p_country NOT LIKE '%'||:ss||'%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "p_name NOT LIKE '%'||:ss||'%'";
    }
    // Year
    else if(column == 3){
        filterStr = "m_name NOT LIKE '%'||:ss||'%'";
    }
    // Built
    else if(column == 4){
        filterStr = "m_type NOT LIKE '%'||:ss||'%'";
    }
    // Type
    else if(column == 5){
        filterStr = "m_system NOT LIKE '%'||:ss||'%'";
    }
    // System
    else if(column == 6){
        filterStr = "p_country NOT LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterConnection(connectionQueryModel, filterStr, searchString, error);
}

// Get connection
bool Services::getConnection(PersonMachine &pm, QString error){
    return dataLayer.getConnection(pm, error);
}
