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

    void searchPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error);
    void filterPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error);
};

#endif // SERVICES_H
