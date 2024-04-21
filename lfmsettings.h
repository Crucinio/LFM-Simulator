
#ifndef LFMSETTINGS_H
#define LFMSETTINGS_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDoubleValidator>

// settings that we will pass to the controller
struct LFMSettings
{
    static constexpr int precision = 5;

    static constexpr double mf_min = 0.00001;
    static constexpr double mf_max = 10000;
    double mf = 0;

    static constexpr double cf_min = 0.00001;
    static constexpr double cf_max = 10000;
    double cf = 0;

    static constexpr double df_min = 0.00001;
    static constexpr double df_max = 10000;
    double df = 0;

    static constexpr double dt_min = 0.00001;
    static constexpr double dt_max = 0.1;
    double dt = 0;
};

// UI class for data input
class LFMSettingsWidget : public QWidget
{
    Q_OBJECT

private:
    // Styling
    QSize min_size = {100, 150};
    int settings_padding_y = 10;

    // layouts
    QVBoxLayout main_layout;
    QHBoxLayout input_layout;
    QVBoxLayout labels_layout;
    QVBoxLayout edits_layout;
    QHBoxLayout buttons_layout;

    // labels
    QLabel settings_label = QLabel(tr("Settings"));
    QLabel mf_label = QLabel(tr("MF, Hz"));
    QLabel cf_label = QLabel(tr("CF, Hz"));
    QLabel df_label = QLabel(tr("DF, Hz"));
    QLabel dt_label = QLabel(tr("dt, sec"));

    // validators
    QDoubleValidator mf_validator = QDoubleValidator(LFMSettings::mf_min, LFMSettings::mf_max, LFMSettings::precision);
    QDoubleValidator cf_validator = QDoubleValidator(LFMSettings::cf_min, LFMSettings::cf_max, LFMSettings::precision);
    QDoubleValidator df_validator = QDoubleValidator(LFMSettings::df_min, LFMSettings::df_max, LFMSettings::precision);
    QDoubleValidator dt_validator = QDoubleValidator(LFMSettings::dt_min, LFMSettings::dt_max, LFMSettings::precision);

    // line edits
    QLineEdit mf_line_edit = QLineEdit("1000");
    QLineEdit cf_line_edit = QLineEdit("0.1");
    QLineEdit df_line_edit = QLineEdit("0.1");
    QLineEdit dt_line_edit = QLineEdit("0.001");

    // buttons
    QPushButton reset_button = QPushButton(tr("RESET"));
    QPushButton pause_button = QPushButton(tr("PAUSE"));

    // opt
    bool paused = false;
public:
    LFMSettingsWidget(QWidget *parent = nullptr);

signals:
    void reset_requested(LFMSettings settings);
    void switch_pause_state();

private slots:
    void process_reset();
    void process_pause();
};

#endif // LFMSETTINGS_H
