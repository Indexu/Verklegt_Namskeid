#ifndef TYPESYSTEM_H
#define TYPESYSTEM_H

#include <QString>

class TypeSystem{
    int Id;
    QString Name;
public:
    // Default
    TypeSystem();

    // Constructor
    TypeSystem(int id, QString name);

    // Get set ID
    int getId() const;
    void setId(int id);

    // Get set name
    QString getName() const;
    void setName(QString name);
};

#endif // TYPESYSTEM_H
