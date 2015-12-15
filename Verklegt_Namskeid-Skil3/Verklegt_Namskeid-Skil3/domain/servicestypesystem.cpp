#include "domain/services.h"

// Get all types
bool Services::getAllTypesSystems(QSqlQueryModel *typeQueryModel, QString &error){
    return dataLayer.getAllTypes(typeQueryModel, error);
}

// Get all systems
bool Services::getAllSystems(QSqlQueryModel *systemQueryModel, QString &error){
    return dataLayer.getAllSystems(systemQueryModel, error);
}

// Search types
bool Services::searchType(QSqlQueryModel *typeQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR name LIKE '%'||:ss||'%' ";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterType(typeQueryModel, filterStr, searchString, error);
}

// Filter type
bool Services::filterType(QSqlQueryModel *typeQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND name NOT LIKE '%'||:ss||'%' ";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterSystem(typeQueryModel, filterStr, searchString, error);
}

// Search system
bool Services::searchSystem(QSqlQueryModel *systemQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR name LIKE '%'||:ss||'%' ";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterSystem(systemQueryModel, filterStr, searchString, error);
}

// Filter system
bool Services::filterSystem(QSqlQueryModel *systemQueryModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND name NOT LIKE '%'||:ss||'%' ";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%'||:ss||'%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%'||:ss||'%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return false;
    }

    // call setFilter
    return dataLayer.filterType(systemQueryModel, filterStr, searchString, error);
}

// Add type / system
bool Services::addTypeSystem(const QString &ts, const bool &type, QString &error){
    return dataLayer.addTypeSystem(ts, type, error);
}

// Delete type / system
bool Services::deleteTypeSystem(const QVector<TypeSystem> &ts, const bool &type, QString &error){
    for(int i = 0; i < ts.size(); i++){
        if(!dataLayer.typeSystemIDExistsDB(ts[i].getId(), type, error)){
            if(error.isEmpty()){
                if(type){
                    error = "Type ID: " + QString::number(ts[i].getId()) + " not found.";
                }
                else{
                    error = "System ID: " + QString::number(ts[i].getId()) + " not found.";
                }
            }
            return false;
        }
    }

    return dataLayer.deleteTypeSystem(ts, type, error);
}

// Get type / system
bool Services::getTypeSystem(TypeSystem &ts, const bool &type, QString &error){
    return dataLayer.getTypeSystem(ts, type, error);
}

// Edit type / system
bool Services::editTypeSystem(const TypeSystem &ts, const bool &type, QString &error){
    return dataLayer.editTypeSystem(ts, type, error);
}
