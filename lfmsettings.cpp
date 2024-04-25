
#include "lfmsettings.h"

#include <QMessageBox>

LFMSettingsWidget::LFMSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    main_layout = new QVBoxLayout(this);
    // styling
    main_layout->setSpacing(settings_padding_y);
    main_layout->setAlignment(Qt::AlignTop);


    // EXPLANATION
    explanation_label = new QLabel("Explanation of terms", this);
    mf_explanation_label = new QLabel("MF - Modulating Frequency", this);
    cf_explanation_label = new QLabel("CF - Carrier Frequensy", this);
    fd_explanation_label = new QLabel("FD - Frequency Deviation", this);
    sf_explanation_label = new QLabel("ST = Sampling Frequency", this);

    main_layout->addWidget(explanation_label);
    main_layout->addWidget(mf_explanation_label);
    main_layout->addWidget(cf_explanation_label);
    main_layout->addWidget(fd_explanation_label);
    main_layout->addWidget(sf_explanation_label);
    // EXPLANATION END

    main_layout->addSpacing(10);

    // CONSTRAINTS
    constraint_label = new QLabel("Constraints", this);
    constraint_mf_label = new QLabel(QString::number(LFMSettings::mf_min) + " < MF < " + QString::number(LFMSettings::mf_max), this);
    constraint_cf_label = new QLabel("1000 > CF > MF", this);
    constraint_fd_label = new QLabel(QString::number(LFMSettings::fd_min) + " < FD < MF", this);
    constraint_sf_label = new QLabel("(CF + FD) * 100 < SF < 1MHz", this);

    main_layout->addWidget(constraint_label);
    main_layout->addWidget(constraint_mf_label);
    main_layout->addWidget(constraint_cf_label);
    main_layout->addWidget(constraint_fd_label);
    main_layout->addWidget(constraint_sf_label);
    // CONSTRAINTS END

    main_layout->addSpacing(10);

    // INPUT
    input_layout = new QHBoxLayout();
    // labels
    input_labels_layout = new QVBoxLayout();
    settings_label = new QLabel("Settings", this);
    mf_label = new QLabel("MF, Hz", this);
    cf_label = new QLabel("CF, Hz", this);
    fd_label = new QLabel("FD, Hz", this);
    sf_label = new QLabel("SF, Hz", this);

    main_layout->addWidget(settings_label);
    input_labels_layout->addWidget(mf_label);
    input_labels_layout->addWidget(cf_label);
    input_labels_layout->addWidget(fd_label);
    input_labels_layout->addWidget(sf_label);

    // line edits
    input_edits_layout = new QVBoxLayout();
    mf_line_edit = new QLineEdit("1", this);
    cf_line_edit = new QLineEdit("100", this);
    fd_line_edit = new QLineEdit("0", this);
    sf_line_edit = new QLineEdit("100000", this);

    mf_validator = new QDoubleValidator(LFMSettings::mf_min, LFMSettings::mf_max, LFMSettings::precision, this);
    cf_validator = new QDoubleValidator(LFMSettings::cf_min, LFMSettings::cf_max, LFMSettings::precision, this);
    fd_validator = new QDoubleValidator(LFMSettings::fd_min, LFMSettings::fd_max, LFMSettings::precision, this);
    sf_validator = new QDoubleValidator(LFMSettings::sf_min, LFMSettings::sf_max, LFMSettings::precision, this);

    QLocale locale("en_US");
    mf_validator->setLocale(locale);
    cf_validator->setLocale(locale);
    fd_validator->setLocale(locale);
    sf_validator->setLocale(locale);

    mf_line_edit->setValidator(mf_validator);
    cf_line_edit->setValidator(cf_validator);
    fd_line_edit->setValidator(fd_validator);
    sf_line_edit->setValidator(sf_validator);
    
    input_edits_layout->addWidget(mf_line_edit);
    input_edits_layout->addWidget(cf_line_edit);
    input_edits_layout->addWidget(fd_line_edit);
    input_edits_layout->addWidget(sf_line_edit);


    input_layout->addLayout(input_labels_layout);
    input_layout->addLayout(input_edits_layout);
    main_layout->addLayout(input_layout);
    // INPUT END

    main_layout->addSpacing(10);

    // CURRENT DATA
    last_data_label = new QLabel("Last input");
    last_mf_label =new QLabel("Last MF = 0.0");
    last_cf_label = new QLabel("Last CF = 0.0");
    last_fd_label = new QLabel("Last FD = 0.0");
    last_sf_label = new QLabel("Last SF = 0.0");

    main_layout->addWidget(last_data_label);
    main_layout->addWidget(last_mf_label);
    main_layout->addWidget(last_cf_label);
    main_layout->addWidget(last_fd_label);
    main_layout->addWidget(last_sf_label);
    // CURRENT DATA END

    main_layout->addWidget(&reset_button);

    // signals
    connect(&reset_button, &QPushButton::clicked, this, &LFMSettingsWidget::process_reset);
}

LFMSettings LFMSettingsWidget::check_settings(bool& ok)
{
    ok = false;

    LFMSettings settings;

    // MF checks
    settings.mf = mf_line_edit->text().toDouble();
    if (settings.mf == 0 || settings.mf < LFMSettings::mf_min || settings.mf > LFMSettings::mf_max)
    {
        notify_input_invalid("Modulating Frequency is invalid. Check constraints for better info.", "!MF INVALID INPUT!");
        return settings;
    }


    // CF checks
    settings.cf = cf_line_edit->text().toDouble();
    if (settings.cf / settings.mf < settings.cf_to_mf_min)
    {
        notify_input_invalid("Carrier Frequency should be " + QString::number(settings.cf_to_mf_min) +
                                 " times higher than Modulating one", "!CF INVALID INPUT!");
        return settings;
    }
    else if (settings.cf / settings.mf > settings.cf_to_mf_max) // threshhold
    {

        notify_input_invalid("With current Carrying Frequency representation will become unreadeble. Bearable frequency: " +
                                 QString::number(settings.mf * settings.cf_to_mf_max), "!CF INVALID INPUT!");
        return settings;
    }

    // FD checks
    settings.fd = fd_line_edit->text().toDouble();
    if (settings.fd > settings.cf)
    {
        notify_input_invalid("Frequency Deviation cannot be higher than Carrier Frequency!", "!FD INVALID INPUT!");
        return settings;
    }

    // SF checks
    settings.sf = sf_line_edit->text().toDouble();
    if (settings.sf < (settings.fd + settings.cf) * LFMSettings::sf_to_cf_x_fd_min)
    {
        notify_input_invalid("Sampling Frequency should at least (CF + FD) * " +
                                 QString::number(settings.sf_to_cf_x_fd_min) +
                                 " = " + QString::number((settings.cf + settings.fd) * settings.sf_to_cf_x_fd_min), "!SF INVALID INPUT!");
        return settings;
    }
    else if (settings.sf / settings.mf > settings.sf_to_mf_max)
    {
        notify_input_invalid("Sampling Frequency / Modulating Frequency upper bound is " + QString::number(settings.sf_to_mf_max), "!SF INVALID INPUT!");
        return settings;
    }

    ok = true;
    return settings;
}

void LFMSettingsWidget::notify_input_invalid(QString msg_text, QString title)
{
    QMessageBox* msg = new QMessageBox();
    connect(msg, &QMessageBox::buttonClicked, msg, &QObject::deleteLater);
    msg->setWindowTitle(title);
    msg->setText(msg_text);
    msg->exec();
}

void LFMSettingsWidget::process_reset()
{
    bool valid = false;
    LFMSettings new_settings = check_settings(valid);
    if (!valid)
        return;

    // updating the "last data" section
    last_mf_label->setText("Last MF = " + mf_line_edit->text());
    last_cf_label->setText("Last CF = " + cf_line_edit->text());
    last_fd_label->setText("Last FD = " + fd_line_edit->text());
    last_sf_label->setText("Last SF = " + sf_line_edit->text());

    //sending new settings
    emit new_data_sent(new_settings);
}
