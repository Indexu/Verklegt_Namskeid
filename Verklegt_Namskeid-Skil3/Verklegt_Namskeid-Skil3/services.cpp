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

bool Services::getAllPersons(QSqlTableModel *personModel, QString &error){
    return dataLayer.getAllPersons(personModel, error);
}

// Search for a person
void Services::searchPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%%1%' OR name LIKE '%%1%' OR gender LIKE '%%1%' OR date_of_birth LIKE '%%1%' OR date_of_death LIKE '%%1%' OR country LIKE '%%1%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%%1%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%%1%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender LIKE '%%1%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth LIKE '%%1%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death LIKE '%%1%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country LIKE '%%1%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return;
    }

    // call setFilter
    dataLayer.setFilterPerson(personModel, filterStr, searchString, error);
}

void Services::filterPerson(QSqlTableModel *personModel, const QString &searchString, const int &column, QString &error)
{
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%%1%' AND name NOT LIKE '%%1%' AND gender NOT LIKE '%%1%' AND date_of_birth NOT LIKE '%%1%' AND date_of_death NOT LIKE '%%1%' AND country NOT LIKE '%%1%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%%1%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%%1%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender NOT LIKE '%%1%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth NOT LIKE '%%1%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death NOT LIKE '%%1%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country NOT LIKE '%%1%'";
    }
    else{
        error = "This is weird... the column is invalid";
        return;
    }

    // call setFilter
    dataLayer.setFilterPerson(personModel, filterStr, searchString, error);
}

bool Services::addPerson(const Person &p, QString &error){
    return dataLayer.addPerson(p, error);
}

bool Services::deletePerson(const int id, QString &error){
    if(dataLayer.personIDExistsDB(id, error)){
        return dataLayer.deletePerson(id, error);
    }
    else if(error.isEmpty()){
        error = "ID: " + QString::number(id) + " not found.";
    }

    return false;
}

bool Services::getPerson(Person &p, QString &error){
    dataLayer.getPerson(p, error);
    qDebug() << p.getCountry();
    return true;
}

