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
// Get type model from data layer
QSortFilterProxyModel *Services::getTypeModel(QSqlQueryModel *&typeQueryModel){
    return dataLayer.getTypeModel(typeQueryModel);
}
// Get system model from data layer
QSortFilterProxyModel *Services::getSystemModel(QSqlQueryModel *&systemQueryModel){
    return dataLayer.getSystemModel(systemQueryModel);
}
