#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayPersonTable();
    void displayMachinesTable();
    void displayPMTable();

private slots:

private:
    Ui::MainWindow *ui;
    Data dataLayer;
};

#endif // MAINWINDOW_H
