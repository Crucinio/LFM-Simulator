
#ifndef AMPLITUDEGRAPHSHANDLER_H
#define AMPLITUDEGRAPHSHANDLER_H

#include "cyclicamplitudegraph.h"
#include "lfmsettings.h"

#include <QVBoxLayout>
#include <QWidget>



class AmplitudeGraphsHandler : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout main_layout;

    CyclicAmplitudeGraph* lfm_graph;
    CyclicAmplitudeGraph* df_graph;

    bool is_paused = false;
    float descreet_time = 0.01f;
public:
    AmplitudeGraphsHandler(QWidget *parent = nullptr);
    ~AmplitudeGraphsHandler();

private slots:
    void update_graphics();
signals:
    void need_update();
public slots:
    void start();
    void reset(LFMSettings settings);
};

#endif // AMPLITUDEGRAPHSHANDLER_H
