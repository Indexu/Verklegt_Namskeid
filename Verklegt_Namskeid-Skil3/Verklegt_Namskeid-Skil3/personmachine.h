#ifndef PERSONMACHINE_H
#define PERSONMACHINE_H

#include <QString>

class PersonMachine
{
    int Id;
    QString P_Name;
    QString P_Country;
    QString M_Name;
    QString M_Type;
    QString M_System;
public:
    // Default
    PersonMachine();

    // Constructor
    PersonMachine(int id, QString p_name, QString p_country, QString m_name, QString m_type, QString m_system);

    // Get set id
    int getId() const;
    void setId(int id);

    // Get set person name
    QString getP_Name() const;
    void setP_Name(QString p_name);

    // Get set person country
    QString getP_Country() const;
    void setP_Country(QString p_country);

    // Get set machine name
    QString getM_Name() const;
    void setM_Name(QString m_name);

    // Get set machine type
    QString getM_Type() const;
    void setM_Type(QString m_type);

    // Get set machine system
    QString getM_System() const;
    void setM_System(QString m_system);

    // Overload == operator
    bool operator==(const PersonMachine &p) const;
};

#endif // PERSONMACHINE_H
