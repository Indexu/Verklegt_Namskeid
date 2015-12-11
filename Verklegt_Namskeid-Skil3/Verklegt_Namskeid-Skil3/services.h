#ifndef SERVICES_H
#define SERVICES_H

#include <QSqlTableModel>
#include "data.h"
#include "person.h"

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

    // Get all persons
    bool getAllPersons(QSqlTableModel *personModel, QString &error);

    // Search person
    void searchPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error);
    // Filter person
    void filterPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error);

    // Add person
    bool addPerson(const Person &p, QString &error);
    // Delete person
    bool deletePerson(const int id, QString &error);
};

#endif // SERVICES_H
