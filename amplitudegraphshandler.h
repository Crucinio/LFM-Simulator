
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

    bool is_paused;
public:
    AmplitudeGraphsHandler(QWidget *parent = nullptr);

public slots:
    void start();
    void reset(LFMSettings settings);
};

#endif // AMPLITUDEGRAPHSHANDLER_H
