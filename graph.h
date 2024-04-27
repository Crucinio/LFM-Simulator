
#ifndef GRAPH_H
#define GRAPH_H


#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QSizeF>
#include <QString>
#include <QRect>

class Graph : public QWidget
{
    Q_OBJECT
private:
    QSizeF world_size = {800, 600};
    QPointF starting_point = {40, 300};
    QSizeF graph_size = {760, 300};

    // symmetrical, only > 0, else does not exist
    double amplitude_y = -1;

    // texts
    QString argument_text = "x";
    QString value_text = "y";
    QString amplitude_text = "";

    // dashing marks (vertical, index to mark text)
    QVector<std::pair<int, QString> > special_marks_x;

    // dashing marks (horizontal, graph y pos to text)
    QVector<std::pair<double, QString> > special_marks_y;

    // arrow sizes
    QSizeF horizontal_arrow = {10, 4}; // (half-height)
    QSizeF vertical_arrow = {4, 8}; // (half-width)

    // colors
    QColor graph_color = Qt::red;
    QColor axis_color = Qt::black;

    // vector of points taken from handler
    QVector<QPointF> points;

    int text_size = 13;
protected:
    void paintEvent(QPaintEvent* event);
public:
    Graph(QWidget *parent = nullptr);
    Graph(QWidget *parent, const QVector<QPointF> &_points);

    QSizeF get_world_size();

    void set_starting_point(QPointF start);
    void set_graph_size(QSizeF size);

    void set_argument_text(QString text);
    void set_value_text(QString text);
    void set_amplitude_text(QString text);

    void set_special_marks_x(QVector<std::pair<int, QString> >& new_marks);
    void set_special_marks_y(QVector<std::pair<double, QString> >& new_marks);

    void set_amplitude(double amplitude);

    void update_points(QVector<QPointF>& new_points);
};

#endif // GRAPH_H
