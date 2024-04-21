
#include "lfmsettings.h"

LFMSettingsWidget::LFMSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    // styling
    main_layout.setSpacing(settings_padding_y);
    main_layout.setAlignment(Qt::AlignTop);

    // labels
    main_layout.addWidget(&settings_label);
    labels_layout.addWidget(&mf_label);
    labels_layout.addWidget(&cf_label);
    labels_layout.addWidget(&df_label);
    labels_layout.addWidget(&dt_label);

    // line edits
    QLocale locale("en_US");
    mf_validator.setLocale(locale);
    cf_validator.setLocale(locale);
    df_validator.setLocale(locale);
    dt_validator.setLocale(locale);

    mf_validator.setNotation(QDoubleValidator::Notation::StandardNotation);
    cf_validator.setNotation(QDoubleValidator::Notation::StandardNotation);
    df_validator.setNotation(QDoubleValidator::Notation::StandardNotation);
    dt_validator.setNotation(QDoubleValidator::Notation::StandardNotation);

    mf_line_edit.setValidator(&mf_validator);
    cf_line_edit.setValidator(&cf_validator);
    df_line_edit.setValidator(&df_validator);
    dt_line_edit.setValidator(&dt_validator);

    edits_layout.addWidget(&mf_line_edit);
    edits_layout.addWidget(&cf_line_edit);
    edits_layout.addWidget(&df_line_edit);
    edits_layout.addWidget(&dt_line_edit);

    // buttons
    buttons_layout.addWidget(&reset_button);
    buttons_layout.addWidget(&pause_button);

    // layouts
    input_layout.addLayout(&labels_layout);
    input_layout.addLayout(&edits_layout);
    main_layout.addLayout(&input_layout);
    main_layout.addLayout(&buttons_layout);
    setLayout(&main_layout);

    // signal - slot system
    connect(&reset_button, &QPushButton::clicked, this, &LFMSettingsWidget::process_reset);
    connect(&pause_button, &QPushButton::clicked, this, &LFMSettingsWidget::process_pause);
}

void LFMSettingsWidget::process_reset()
{
    emit reset_requested({mf_line_edit.text().toDouble(),
                          cf_line_edit.text().toDouble(),
                          df_line_edit.text().toDouble(),
                          dt_line_edit.text().toDouble()});
}

void LFMSettingsWidget::process_pause()
{
    paused ? pause_button.setText("PAUSE") : pause_button.setText("CONTINUE");
    paused = !paused;
    emit switch_pause_state();
}
