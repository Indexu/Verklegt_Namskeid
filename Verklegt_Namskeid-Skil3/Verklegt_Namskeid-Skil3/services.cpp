#include "services.h"

// Constructor
Services::Services(){

}

// ===== MODELS =====
// Get person model from data layer
QSqlQueryModel *Services::getPersonModel(){
    return dataLayer.getPersonModel();
}
// Get machine model from data layer
QSqlQueryModel *Services::getMachineModel(){
    return dataLayer.getMachineModel();
}
// Get connection model from data layer
QSqlQueryModel *Services::getConnectionModel(){
    return dataLayer.getConnectionModel();
}

// Get all persons
bool Services::getAllPersons(QSqlQueryModel *personModel, QString &error){
    return dataLayer.getAllPersons(personModel, error);
}

// Search for a person
bool Services::searchPerson(QSqlQueryModel *personModel, const QString &searchString, const int &column, QString &error){
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%'||:ss||'%' OR name LIKE '%'||:ss||'%' OR gender LIKE '%'||:ss||'%' OR date_of_birth LIKE '%'||:ss||'%' OR date_of_death LIKE '%'||:ss||'%' OR country LIKE '%'||:ss||'%'";
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
    return dataLayer.filterPerson(personModel, filterStr, searchString, error);
}

// Filter person
bool Services::filterPerson(QSqlQueryModel *personModel, const QString &searchString, const int &column, QString &error)
{
    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%'||:ss||'%' AND name NOT LIKE '%'||:ss||'%' AND gender NOT LIKE '%'||:ss||'%' AND date_of_birth NOT LIKE '%'||:ss||'%' AND date_of_death NOT LIKE '%'||:ss||'%' AND country NOT LIKE '%'||:ss||'%'";
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
    return dataLayer.filterPerson(personModel, filterStr, searchString, error);
}

// Add person
bool Services::addPerson(const Person &p, QString &error){
    return dataLayer.addPerson(p, error);
}

// Delete person
bool Services::deletePerson(const int id, QString &error){
    if(dataLayer.personIDExistsDB(id, error)){
        return dataLayer.deletePerson(id, error);
    }
    else if(error.isEmpty()){
        error = "ID: " + QString::number(id) + " not found.";
    }

    return false;
}

<<<<<<< HEAD
bool Services::getPerson(Person &p, QString &error){
    dataLayer.getPerson(p, error);
    qDebug() << p.getCountry();
    return true;
=======
// Edit person
bool Services::editPerson(const Person &p, QString &error){
    return dataLayer.editPerson(p, error);
>>>>>>> origin/master
}

