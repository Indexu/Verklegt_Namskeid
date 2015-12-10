#ifndef MACHINE_H
#define MACHINE_H

#include <QString>

class Machine{
    int Id;
    QString Name;
    int Year;
    bool Built;
    QString Type;
    QString System;
public:
    // Default
    Machine();

    // Constructor
    Machine(int id, QString n, int y, bool b, QString t, QString s);

    // GETTERS/SETTERS
    // Get/set machine ID
    int getId() const;
    void setId(int id);

    // Get/set year build year
    int getYear() const;
    void setYear(int y);

    // Get/set if machine is built
    bool getBuilt() const;
    void setBuilt(bool b);

    // Get/set machine name
    QString getName() const;
    void setName(QString n);

    // Get/set machine type
    QString getType() const;
    void setType(QString t);

    // Get/set machine numerical system
    QString getSystem() const;
    void setSystem(QString s);

    // Overload == operator
    bool operator==(const Machine &p) const;

};

#endif // MACHINE_H

