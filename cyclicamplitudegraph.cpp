
#include "cyclicamplitudegraph.h"

#include <QFontMetricsF>
void CyclicAmplitudeGraph::paintEvent(QPaintEvent *event)
{
    // prep
    QPen pen(axis_color);
    QFont font("times");
    QFontMetricsF fmf(font);
    QPointF world_to_screen = {width() / world_size.width(), height() / world_size.height()};
    QPixmap frame(size());
    frame.fill();

    QPainter painter(&frame);
    painter.setPen(pen);
    painter.setFont(font);

    // Axises
    // Ox
    painter.drawLine(0, size().height() / 2, size().width(), size().height() / 2);
    painter.drawText(size().width() - fmf.horizontalAdvance(text_x), size().height() / 2 - text_boundig_rect.height() / 2, text_x);

    // Oy
    painter.drawLine(padding.width() * world_to_screen.x(), 0, padding.width() * world_to_screen.x(), height());
    painter.drawText((padding.width() + fmf.horizontalAdvance('1')) * world_to_screen.x(), fmf.height() / 1.5f,  text_y);

    // Amplitude
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawLine(padding.width() * world_to_screen.x(), padding.height() * world_to_screen.y(), width(), padding.height() * world_to_screen.y());
    painter.drawLine(padding.width() * world_to_screen.x(), height() - padding.height() * world_to_screen.y(), width(), height() - padding.height() * world_to_screen.y());

    // Graph
    pen.setColor(graph_color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for (int i = 0; i < points_x.size() - 1; ++i)
    {
        painter.drawLine(points_x[i] * world_to_screen.x(),
                         points_y[i] * world_to_screen.y(),
                         points_x[i + 1] * world_to_screen.x(),
                         points_y[i + 1] * world_to_screen.y());
    }
    painter.end();

    // copying to Widget canvas
    //frame = frame.scaled()
    painter.begin(this);
    painter.drawPixmap(0, 0, frame);
    painter.end();

    QWidget::paintEvent(event);
}

CyclicAmplitudeGraph::CyclicAmplitudeGraph(QWidget *parent) : QWidget{parent}
{
    setMinimumSize(400, 300);
}

CyclicAmplitudeGraph::CyclicAmplitudeGraph(QWidget *parent, const QVector<QPointF> &_points) : CyclicAmplitudeGraph(parent)
{
    points_x.reserve(_points.size());
    points_y.reserve(_points.size());
    for (auto& point : _points)
    {
        points_x.emplaceBack(point.x());
        points_y.emplaceBack(point.y());
    }
}

QSizeF CyclicAmplitudeGraph::get_padding() const
{
    return padding;
}

void CyclicAmplitudeGraph::set_text_x(QString &text)
{
    text_x = text;
}

void CyclicAmplitudeGraph::set_text_y(QString &text)
{
    text_y = text;
}

void CyclicAmplitudeGraph::update_points(QVector<QPointF> &new_points)
{
    points_x.clear();
    points_y.clear();
    points_x.reserve(new_points.size());
    points_y.reserve(new_points.size());
    for (auto& point : new_points)
    {
        points_x.emplaceBack(point.x());
        points_y.emplaceBack(point.y());
    }
}

void CyclicAmplitudeGraph::advance_by(int frames)
{
    if (points_x.empty())
        return;

    frames = frames % points_x.size();
    auto it = points_y.begin();
    std::advance(it, frames);
    std::rotate(points_y.begin(), it, points_y.end());
}
