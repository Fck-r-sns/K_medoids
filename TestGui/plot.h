#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

class Plot : public QWidget
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = 0);

signals:
    void sig_mouseClicked(double x, double y);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PLOT_H
