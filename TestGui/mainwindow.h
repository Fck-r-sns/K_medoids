#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
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

    static double distanceFunc(const Algo::Tuple &t1, const Algo::Tuple &t2);

private:
    Algo m_kMedoids;
    Algo::Data m_data;
    std::vector<Algo::Cluster> m_clusters;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
