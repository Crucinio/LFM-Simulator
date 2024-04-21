
#include "lfmwidget.h"


LFMWidget::LFMWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);
    // init
    settings_widget = new LFMSettingsWidget(this);


    // styling
    main_layout.setAlignment(Qt::AlignTop);
    graphs.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settings_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // layouts
    main_layout.addWidget(settings_widget);
    main_layout.addWidget(&graphs);

    setLayout(&main_layout);

    // signal-slot
    connect(settings_widget, &LFMSettingsWidget::reset_requested, &graphs, &AmplitudeGraphsHandler::reset);
}

LFMWidget::~LFMWidget()
{

}


