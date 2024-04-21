
#ifndef CYCLICAMPLITUDEGRAPH_H
#define CYCLICAMPLITUDEGRAPH_H


#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QSizeF>
#include <QString>
#include <QRect>

class PointF : public QPointF
{
public:
    QPointF operator * (QPointF& other) {return {x() * other.x(), y() * other.y() };}
};

class CyclicAmplitudeGraph : public QWidget
{
    Q_OBJECT
private:
    // colors
    QColor graph_color = Qt::red;
    QColor axis_color = Qt::black;

    // axis naming
    QString text_y = "";
    QString text_x = "";

    // vector of points
    QVector<QPointF> points = QVector<QPointF>();
    // gor easier advancing
    QVector<float> points_x;
    QVector<float> points_y;
    int current_starting_point = 0;

    // screening
    QRect text_boundig_rect = {0, 0, 5, 13};
    int text_size = 13;
    QSizeF padding = {40.0f, 60.0f};
protected:
    void paintEvent(QPaintEvent* event);
public:
    CyclicAmplitudeGraph(QWidget *parent = nullptr);
    CyclicAmplitudeGraph(QWidget *parent, const QVector<QPointF> &_points);

    QSizeF get_padding() const;
    int get_current_frame() const;

    void set_text_x(QString& text);
    void set_text_y(QString& text);

    void update_points(QVector<QPointF>& new_points);

    static constexpr QSizeF world_size = { 800.0f, 600.0f };
public slots:
    void advance_by(int frames);
    void set_current_starting_point(int index);
};

#endif // CYCLICAMPLITUDEGRAPH_H
