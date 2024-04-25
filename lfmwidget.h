
#ifndef LFMWIDGET_H
#define LFMWIDGET_H

#include "lfmsettings.h"
#include "amplitudegraphshandler.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


class LFMWidget : public QWidget

{
    Q_OBJECT

private:
    // SettingsWidget
    LFMSettingsWidget* settings_widget;

    // Graphs
    GraphHandler graphs = GraphHandler(this);

    QHBoxLayout main_layout;
public:
    LFMWidget(QWidget *parent = nullptr);
    ~LFMWidget();
};

#endif // LFMWIDGET_H
