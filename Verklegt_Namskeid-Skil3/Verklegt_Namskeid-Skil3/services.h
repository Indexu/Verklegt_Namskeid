#ifndef SERVICES_H
#define SERVICES_H

#include <QSqlTableModel>
#include "data.h"

class Services
{
    // Data layer instance
    Data dataLayer;
public:
    // Constructor
    Services();

    // Get person model from data layer
    QSqlTableModel* getPersonModel(QObject *parent);
    // Get machine model from data layer
    QSqlTableModel* getMachineModel(QObject *parent);
    // Get connection model from data layer
    QSqlTableModel* getConnectionModel(QObject *parent);
};

#endif // SERVICES_H
