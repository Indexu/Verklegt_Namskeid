#include "domain/services.h"

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
