#ifndef UTILITIES_H
#define UTILITIES_H

#include "models/person.h"
#include "models/machine.h"
#include "models/personmachine.h"
#include <QTableView>

// = UTILITY FUNCTIONS =

namespace utilities{
    // Get IDs of selected rows of a QTableView
    QVector<int> getSelectedTableViewIds(QTableView *table);

    // Get column data as string from QModelIndex and QTableView
    QString getColumnData(QTableView *table, const QModelIndex &index, const int &col);

    // Resize columns
    void resizeTableColumns(QTableView *table);
}

#endif // UTILITIES_H
