
#ifndef AMPLITUDEGRAPHSHANDLER_H
#define AMPLITUDEGRAPHSHANDLER_H

#include "cyclicamplitudegraph.h"
#include "lfmsettings.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>


class AmplitudeGraphsHandler : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout main_layout;

    CyclicAmplitudeGraph* lfm_graph;
    CyclicAmplitudeGraph* df_graph;

    QSlider* frame_slider;

    bool is_paused = false;
    float descreet_time = 0.01f;
    int frame_value = 0;
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
    void process_slider(int val);
};

#endif // AMPLITUDEGRAPHSHANDLER_H
