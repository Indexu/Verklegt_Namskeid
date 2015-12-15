#include "utilities.h"

namespace utilities{
    // Get IDs of selected rows of a QTableView
    QVector<int> getSelectedTableViewIds(QTableView *table){
        QVector<int> ids;

        // Get rows
        QModelIndexList selection = table->selectionModel()->selectedRows();

        // No rows
        if (selection.isEmpty()) {
            return ids;
        }

        int id = 0;
        for(int i = 0; i < selection.count();i++){
            // Get first column (id)
            QModelIndex index = selection.at(i);
            // Get id column data
            id = table->model()->data(index).toInt();

            ids.push_back(id);
        }

        return ids;
    }

}
