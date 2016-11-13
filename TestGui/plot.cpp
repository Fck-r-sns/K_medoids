#include "plot.h"
#include <QPainter>
#include <QMouseEvent>

const double POINT_RADIUS = 4.0;
const double MEDOID_BORDER_WIDTH = 3.0;
const Qt::GlobalColor POINT_COLOR = Qt::black;
const Qt::GlobalColor COLORS[] = {
    Qt::red,
    Qt::blue,
    Qt::green,
    Qt::cyan,
    Qt::magenta,
    Qt::yellow,
    Qt::darkRed,
    Qt::darkGreen,
    Qt::darkBlue,
    Qt::darkCyan,
    Qt::darkMagenta,
    Qt::darkYellow,
    Qt::darkGray,
    Qt::gray,
    Qt::lightGray
};
const int COLOR_COUNT = sizeof(COLORS) / sizeof(Qt::GlobalColor);

Plot::Plot(QWidget *parent)
    : QWidget(parent)
{
}

void Plot::setData(const Algo::Data *data)
{
    m_data = data;
}

void Plot::setClusters(const std::vector<Algo::Cluster> *clusters)
{
    m_clusters = clusters;
}

void Plot::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    const double w = width() - 1;
    const double h = height() - 1;
    painter.drawLine(0, 0, 0, h);
    painter.drawLine(0, 0, w, 0);
    painter.drawLine(0, h, w, h);
    painter.drawLine(w, 0, w, h);

    if (!m_data) {
        return;
    }

    auto drawTuple = [&painter, w, h](const Algo::Tuple &tuple) {
        const auto x = std::get<0>(tuple) * w;
        const auto y = std::get<1>(tuple) * h;
        painter.drawEllipse(QPointF(x, y), POINT_RADIUS, POINT_RADIUS);
    };

    if (!m_clusters) {
        painter.setPen(Qt::transparent);
        painter.setBrush(POINT_COLOR);
        for (const Algo::Tuple &tuple : *m_data) {
            drawTuple(tuple);
        }
    } else {
        int colorIdx = 0;
        for (const Algo::Cluster &cluster : *m_clusters) {
            painter.setPen(Qt::transparent);
            painter.setBrush(COLORS[colorIdx]);
            colorIdx = (colorIdx + 1) % COLOR_COUNT;
            for (int tupleIdx : cluster.indices) {
                const auto &tuple = m_data->at(tupleIdx);
                drawTuple(tuple);
            }
            painter.setPen(QPen(Qt::black, MEDOID_BORDER_WIDTH));
            drawTuple(cluster.center);
        }
    }
}

void Plot::mousePressEvent(QMouseEvent *event)
{
    const auto pos = event->pos();
    emit sig_mouseClicked(pos.x() / (double) width(), pos.y() / (double) height());
}
