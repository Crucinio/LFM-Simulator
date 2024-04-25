
#ifndef AMPLITUDEGRAPHSHANDLER_H
#define AMPLITUDEGRAPHSHANDLER_H

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
public:
    GraphHandler(QWidget *parent = nullptr);
    ~GraphHandler();
public slots:
    void reset(LFMSettings settings);
    // void process_slider(int val);
};

#endif // AMPLITUDEGRAPHSHANDLER_H
