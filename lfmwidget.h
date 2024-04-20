
#ifndef LFMWIDGET_H
#define LFMWIDGET_H

#include "lfmsettings.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


class LFMWidget : public QWidget

{
    Q_OBJECT

private:
    // SettingsWidget
    LFMSettingsWidget* settings_widget;
public:
    LFMWidget(QWidget *parent = nullptr);
    ~LFMWidget();
};

#endif // LFMWIDGET_H
