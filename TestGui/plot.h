#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include "defines.h"

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = 0);

    void setData(const Algo::Data *data);
    void setClusters(const std::vector<Algo::Cluster> *clusters);

signals:
    void sig_mouseClicked(double x, double y);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    const Algo::Data *m_data = nullptr;
    const std::vector<Algo::Cluster> *m_clusters = nullptr;
};

#endif // PLOT_H
