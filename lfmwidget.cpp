
#include "lfmwidget.h"


LFMWidget::LFMWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);

    // styling
    main_layout->setAlignment(Qt::AlignTop);
    graphs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settings_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // layouts
    main_layout->addWidget(settings_widget);
    main_layout->addWidget(graphs);

    // signal-slot
    connect(settings_widget, &LFMSettingsWidget::new_data_sent, graphs, &GraphHandler::reset);
}


