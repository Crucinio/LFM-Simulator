
#include "graph.h"

#include <QFontMetricsF>
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
    painter.drawText(width() - fmf.horizontalAdvance(argument_text), y0 - text_size / 2, argument_text);

    // Oy
    painter.drawLine(x0, 0, x0, height());
    painter.drawText(x0 + fmf.horizontalAdvance('1'), fmf.height() / 1.5f,  value_text);

    // Amplitude (OPTIONAL)
    if (amplitude_y > 0)
    {
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        // -
        painter.drawLine(x0, y0 + amplitude_y * world_to_screen.y(), width(), y0 + amplitude_y * world_to_screen.y());
        painter.drawText(x0 + fmf.horizontalAdvance('1'), y0 + amplitude_y * world_to_screen.y(), "-" + amplitude_text);

        // +
        painter.drawLine(x0, y0 - amplitude_y * world_to_screen.y(), width(), y0 - amplitude_y * world_to_screen.y());
        painter.drawText(x0 + fmf.horizontalAdvance('1'), y0 - amplitude_y * world_to_screen.y(), amplitude_text);
    }

    // Graph
    pen.setColor(graph_color);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    double dx = 0;
    if (!points.empty())
        dx = (1.0f / points.size()) * (width() - 2 * x0);

    for (int i = 0; i < points.size() - 1; ++i)
    {
        painter.drawLine(x0 + dx * i,
                         y0 + points[i].y() * (height() / 2 - 50 * world_to_screen.y()),
                         x0 + dx * i,
                         y0 +  points[i + 1].y() * (height() / 2 - 50 * world_to_screen.y()));
    }
    painter.end();

    // copying to Widget canvas
    //frame = frame.scaled()
    painter.begin(this);
    painter.drawPixmap(0, 0, frame);
    painter.end();

    QWidget::paintEvent(event);
}

Graph::Graph(QWidget *parent) : QWidget{parent}
{
    setMinimumSize(400, 300);
}

Graph::Graph(QWidget *parent, const QVector<QPointF> &_points) : Graph(parent)
{
    points = _points;
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

void Graph::set_amplitude(double amplitude)
{
    amplitude_y = amplitude;
}

void Graph::set_x_multiplier(double mult)
{
    x_multiplier = mult;
}

void Graph::update_points(QVector<QPointF> &new_points)
{
    points = new_points;
}
