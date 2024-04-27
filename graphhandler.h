
#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include "graph.h"
#include "lfmsettings.h"

#include <QTabWidget>

class GraphHandler : public QTabWidget
{
    Q_OBJECT
private:
    Graph* lfm_time_graph;
    Graph* lfm_frequency_graph;

    // s(t)
    void fill_points_time_domain(QVector<QPointF>& points, double period, double sampling_frequency,double carrier_frequency, double deviation);

    // DFT s(t) -> s(w)
    void fill_points_frequency_domain(QVector<QPointF>& points_container, const QVector<QPointF>& time_domain_points, double boundary);
    double calculate_imaginary_part(const QVector<QPointF>& time_domain_points, int k);
    double calculate_real_part(const QVector<QPointF>& time_domain_points, int k);
public:
    GraphHandler(QWidget *parent = nullptr);
    ~GraphHandler() = default;
public slots:
    void reset(LFMSettings settings);
};

#endif // GRAPHHANDLER_H
