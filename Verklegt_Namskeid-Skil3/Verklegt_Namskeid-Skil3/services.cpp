#include "services.h"

// Constructor
Services::Services(){

}

// ===== MODELS =====
// Get person model from data layer
QSqlTableModel *Services::getPersonModel(QObject *parent){
    return dataLayer.getPersonModel(parent);
}
// Get machine model from data layer
QSqlTableModel *Services::getMachineModel(QObject *parent){
    return dataLayer.getMachineModel(parent);
}
// Get connection model from data layer
QSqlTableModel *Services::getConnectionModel(QObject *parent){
    return dataLayer.getConnectionModel(parent);
}

