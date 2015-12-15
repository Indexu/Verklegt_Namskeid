#ifndef UTILITIES_H
#define UTILITIES_H

#include "models/person.h"
#include "models/machine.h"
#include "models/personmachine.h"
#include <regex>
#include <string>
#include <QTableView>

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

    // Get IDs of selected rows of a QTableView
    QVector<int> getSelectedTableViewIds(QTableView *table);
}

#endif // UTILITIES_H
