#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("K-medoids test app");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearAllPoints()
{
    m_data.clear();
    ui->plotWidget->update();
}

void MainWindow::addNewPoint(double x, double y)
{
    m_data.emplace_back(x, y);
    ui->plotWidget->update();
}
