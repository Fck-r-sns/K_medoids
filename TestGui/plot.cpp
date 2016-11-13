#include "plot.h"
#include <QPainter>
#include <QMouseEvent>

Plot::Plot(QWidget *parent)
    : QWidget(parent)
{
}

void Plot::setData(const Algo::Data *data)
{
    m_data = data;
}

void Plot::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    const auto w = width() - 1;
    const auto h = height() - 1;
    painter.drawLine(0, 0, 0, h);
    painter.drawLine(0, 0, w, 0);
    painter.drawLine(0, h, w, h);
    painter.drawLine(w, 0, w, h);
}

void Plot::mousePressEvent(QMouseEvent *event)
{
    const auto pos = event->pos();
    emit sig_mouseClicked(pos.x(), pos.y());
}
