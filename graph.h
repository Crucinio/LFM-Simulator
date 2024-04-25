
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
    QSizeF graph_size = {800, 600};

    // symmetrical, only > 0, else does not exist
    double amplitude_y = -1;

    // texts
    QString argument_text = "x";
    QString value_text = "y";
    QString amplitude_text = "";

    // horizontal axis mark division, from x0 to width - x0
    int x_marks_amount;

    // vertical axis mark divisiom, one way from y0 to graph zone y and then reflected
    int y_marks_amount;

    // colors
    QColor graph_color = Qt::red;
    QColor axis_color = Qt::black;

    // vector of points taken from handler
    QVector<QPointF> points;

    int text_size = 13;
    double x_multiplier = 1;
protected:
    void paintEvent(QPaintEvent* event);
public:
    Graph(QWidget *parent = nullptr);
    Graph(QWidget *parent, const QVector<QPointF> &_points);

    QSizeF get_world_size();

    void set_starting_point(QPointF start);

    void set_argument_text(QString text);
    void set_value_text(QString text);
    void set_amplitude_text(QString text);

    void set_x_marks_amount(int new_amount);
    void set_y_marks_amount(int new_amount);

    void set_amplitude(double amplitude);

    void set_x_multiplier(double mult);

    void update_points(QVector<QPointF>& new_points);
};

#endif // GRAPH_H
