#ifndef PERSON
#define PERSON

#include <QString>
#include <vector>

class Person{
    int Id;
    QString Name;
    QString Gender;
    QString DateOfBirth;
    QString DateOfDeath;
    QString Country;
public:
    // Default
    Person();

    // Constructor
    Person(int id, QString n, QString g, QString dob, QString dod, QString c);

    // Get id
    int getId() const;

    // Get set name
    QString getName() const;
    void setName(QString n);

    // Get set gender
    QString getGender() const;
    void setGender(QString);

    // Get set date of birth
    QString getDateOfBirth() const;
    void setDateOfBirth(QString dob);

    // Get set date of death
    QString getDateOfDeath() const;
    void setDateOfDeath(QString dod);

    // Get set country
    QString getCountry() const;
    void setCountry(QString c);

    // Overload == operator
    bool operator==(const Person &p) const;

};

#endif // PERSON

