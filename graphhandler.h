
#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include "graph.h"
#include "lfmsettings.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QTabWidget>


class GraphHandler : public QTabWidget
{
    Q_OBJECT
private:
    Graph* lfm_time_graph;
    Graph* lfm_frequency_graph;

    void fill_points_time_domain(QVector<QPointF>& points, double period, double sampling_frequency,double carrier_frequency, double deviation);

    // DPF
    void fill_points_frequency_domain(QVector<QPointF>& points_container, const QVector<QPointF>& time_domain_points, double boundary);
    double calculate_imaginary_part(const QVector<QPointF>& time_domain_points, int k);
    double calculate_real_part(const QVector<QPointF>& time_domain_points, int k);
public:
    GraphHandler(QWidget *parent = nullptr);
    ~GraphHandler();
public slots:
    void reset(LFMSettings settings);
    // void process_slider(int val);
};

#endif // GRAPHHANDLER_H
