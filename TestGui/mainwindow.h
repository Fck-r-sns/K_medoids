#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "defines.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void clearAllPoints();
    void addNewPoint(double x, double y);
    void runClustering();

private:
    Algo m_kMedoids;
    Algo::Data m_data;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
