
#include "lfmwidget.h"


LFMWidget::LFMWidget(QWidget *parent)
    : QWidget(parent)
{
    settings_widget = new LFMSettingsWidget(this);
}

LFMWidget::~LFMWidget()
{
}


