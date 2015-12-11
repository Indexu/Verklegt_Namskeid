#ifndef UTILITIES_H
#define UTILITIES_H

#include "person.h"
#include "machine.h"
#include "personmachine.h"
#include <regex>
#include <string>

// = UTILITY FUNCTIONS =

namespace utilities{
    // Verify date
    bool verifyDate(const QString &ver);

    // Verify QString as number
    bool isNumber(const QString &str);

    // Convert 1's and 0's to yes and no
    QString boolYesNo(bool num);

    // Yes no to bool
    bool QStringBool(QString s);
}

#endif // UTILITIES_H
