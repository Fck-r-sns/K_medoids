#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plotWidget->setData(&m_data);
    ui->plotWidget->setClusters(&m_clusters);

    setWindowTitle("K-medoids test app");

    connect(ui->plotWidget, &Plot::sig_mouseClicked, this, &MainWindow::addNewPoint);

    m_kMedoids.setData(&m_data);
    m_kMedoids.setDistanceFunc(MainWindow::distanceFunc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearAllPoints()
{
    m_data.clear();
    m_clusters.clear();
    ui->plotWidget->update();
}

void MainWindow::addNewPoint(double x, double y)
{
    m_data.emplace_back(x, y);
    ui->plotWidget->update();
}

void MainWindow::runClustering()
{
    m_clusters = m_kMedoids
            .setNumberOfClusters(ui->kInput->value())
            .go();
    ui->plotWidget->update();
}

double MainWindow::distanceFunc(const Algo::Tuple &t1, const Algo::Tuple &t2)
{
    const auto x1 = std::get<0>(t1);
    const auto y1 = std::get<1>(t1);
    const auto x2 = std::get<0>(t2);
    const auto y2 = std::get<1>(t2);
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}
