#include "domain/services.h"

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
