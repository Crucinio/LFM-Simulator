
#include "graph.h"

#include <QFontMetricsF>
#include <QPixmap>
#include <QPainter>

void Graph::paintEvent(QPaintEvent *event)
{
    // prep
    QPen pen(axis_color);
    QFont font;
    font.setPointSize(10);
    QFontMetricsF fmf(font);
    QPointF world_to_screen = {width() / world_size.width(), height() / world_size.height()};
    QPixmap frame(size());
    frame.fill();

    QPainter painter(&frame);
    painter.setPen(pen);
    painter.setFont(font);
    //painter.setRenderHint(QPainter::Antialiasing);

    // Axises
    double x0 = starting_point.x() * world_to_screen.x();
    double y0 = starting_point.y() * world_to_screen.y();

    // Ox
    painter.drawLine(0, y0, size().width(), y0);
    painter.drawLine(size().width(), y0, size().width() - horizontal_arrow.width(), y0 - horizontal_arrow.height());
    painter.drawLine(size().width(), y0, size().width() - horizontal_arrow.width(), y0 + horizontal_arrow.height());
    painter.drawText(width() - fmf.horizontalAdvance(argument_text), y0 - fmf.height() / 2, argument_text);

    // Oy
    painter.drawLine(x0, 0, x0, height());
    painter.drawLine(x0, 0, x0 + vertical_arrow.width(), vertical_arrow.height());
    painter.drawLine(x0, 0, x0 - vertical_arrow.width(), vertical_arrow.height());
    painter.drawText(x0 + fmf.horizontalAdvance('1'), fmf.height() / 1.5f,  value_text);

    // Amplitude
    if (amplitude_y > 0)
    {
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        // -
        painter.drawLine(0, y0 + amplitude_y * world_to_screen.y(), width(), y0 + amplitude_y * world_to_screen.y());
        painter.drawText(x0 + fmf.horizontalAdvance('1'), y0 + amplitude_y * world_to_screen.y(), "-" + amplitude_text);

        // +
        painter.drawLine(0, y0 - amplitude_y * world_to_screen.y(), width(), y0 - amplitude_y * world_to_screen.y());
        painter.drawText(x0 + fmf.horizontalAdvance('1'), y0 - amplitude_y * world_to_screen.y(), amplitude_text);
    }

    double dx = 0;
    if (!points.empty())
        dx = (graph_size.width() / points.size()) * world_to_screen.x();

    // Graph
    pen.setColor(graph_color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);


    for (int i = 0; i < points.size() - 1; ++i)
    {
        painter.drawLine(x0 + dx * points[i].x(),
                         y0 - points[i].y() * graph_size.height() * world_to_screen.y(),
                         x0 + dx * points[i + 1].x(),
                         y0 - points[i + 1].y() * graph_size.height() * world_to_screen.y());
    }

    pen.setColor(axis_color);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);

    // Special marks x
    for (auto& mark : special_marks_x)
    {
        painter.drawLine(points[mark.first].x() * dx + x0, 0, points[mark.first].x() * dx + x0, height());
        painter.drawText(points[mark.first].x() * dx + x0, y0 + fmf.height() / 1.5f, mark.second);
    }

    // Special marks y
    for (auto& mark : special_marks_y)
    {
        painter.drawLine(0, y0 - mark.first * height(), width(), y0 - mark.first * height());
        painter.drawText(x0, y0 - mark.first * height(), mark.second);
    }

    painter.end();

    // copying to Widget canvas
    painter.begin(this);
    painter.drawPixmap(0, 0, frame);
    painter.end();

    QWidget::paintEvent(event);
}

Graph::Graph(QWidget *parent) : QWidget{parent}
{
    setMinimumSize(400, 300);
}

QSizeF Graph::get_world_size()
{
    return world_size;
}

void Graph::set_starting_point(QPointF start)
{
    starting_point = start;
}

void Graph::set_graph_size(QSizeF size)
{
    graph_size = size;
}

void Graph::set_argument_text(QString text)
{
    argument_text = text;
}

void Graph::set_value_text(QString text)
{
    value_text = text;
}

void Graph::set_amplitude_text(QString text)
{
    amplitude_text = text;
}

void Graph::set_special_marks_x(const QVector<std::pair<int, QString> > &new_marks)
{
    special_marks_x = new_marks;
}

void Graph::set_special_marks_y(const QVector<std::pair<double, QString> > &new_marks)
{
    special_marks_y = new_marks;
}

void Graph::set_amplitude(double amplitude)
{
    amplitude_y = amplitude;
}

void Graph::update_points(const QVector<QPointF> &new_points)
{
    points = new_points;
}
