
#ifndef LFMWIDGET_H
#define LFMWIDGET_H

#include "lfmsettings.h"
#include "graphhandler.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


class LFMWidget : public QWidget

{
    Q_OBJECT

private:
    // SettingsWidget
    LFMSettingsWidget* settings_widget = new LFMSettingsWidget(this);

    // Graphs
    GraphHandler* graphs = new GraphHandler(this);

    QHBoxLayout* main_layout = new QHBoxLayout(this);
public:
    LFMWidget(QWidget *parent = nullptr);
    ~LFMWidget() = default;
};

#endif // LFMWIDGET_H
