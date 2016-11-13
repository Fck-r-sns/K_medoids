#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../k_medoids/KMedoidsClustering.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using Algo = KMedoidsClustering<double, double>;

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
