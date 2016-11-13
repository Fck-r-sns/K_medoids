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

signals:
    void sig_mouseClicked(double x, double y);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    const Algo::Data *m_data = nullptr;
};

#endif // PLOT_H
