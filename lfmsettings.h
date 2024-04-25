
#ifndef LFMSETTINGS_H
#define LFMSETTINGS_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDoubleValidator>
#include <QCheckBox>

// settings that we will pass to the controller
struct LFMSettings
{
    static constexpr int precision = 10;

    // Modulating frequency
    static constexpr double mf_min = 0.1;
    static constexpr double mf_max = 100;
    double mf = 1;

    // carrying frequency
    static constexpr double cf_min = 1;
    static constexpr double cf_max = 10000;
    double cf = 10;

    // frequency deviation
    static constexpr double fd_min = 0;
    static constexpr double fd_max = 10000;
    double fd = 0;

    // sampling frequency
    static constexpr double sf_min = 100;
    static constexpr double sf_max = 10000000;
    double sf = 100;;

    // relative constraints
    static constexpr double cf_to_mf_min = 5;
    static constexpr double cf_to_mf_max = 1000;

    static constexpr double sf_to_cf_x_fd_min = 100;
    static constexpr double sf_to_mf_max = 10000000;
};

// UI class for data input
class LFMSettingsWidget : public QWidget
{
    Q_OBJECT

private:
    // Styling
    QSize min_size = {100, 150};
    int settings_padding_y = 5;

    // layouts
    QVBoxLayout* main_layout;
    QHBoxLayout* input_layout;
    QVBoxLayout* input_labels_layout;
    QVBoxLayout* input_edits_layout;

    // EXPLANATION
    QLabel* explanation_label;
    QLabel* mf_explanation_label;
    QLabel* cf_explanation_label;
    QLabel* fd_explanation_label;
    QLabel* sf_explanation_label;

    // CONSTRAINTS
    QLabel* constraint_label;
    QLabel* constraint_mf_label;
    QLabel* constraint_cf_label;
    QLabel* constraint_fd_label;
    QLabel* constraint_sf_label;
    // CONSTRAINS END

    // INPUT
    // labels
    QLabel* settings_label;
    QLabel* mf_label;
    QLabel* cf_label;
    QLabel* fd_label;
    QLabel* sf_label;

    // line edits
    QLineEdit* mf_line_edit;
    QLineEdit* cf_line_edit;
    QLineEdit* fd_line_edit;
    QLineEdit* sf_line_edit;
    // INPUT END

    // LAST INPUT DATA
    QLabel* last_data_label;
    QLabel* last_mf_label;
    QLabel* last_cf_label;
    QLabel* last_fd_label;
    QLabel* last_sf_label;
    // LAST INPUT DATA END

    // input chats validators, could have used regex validator, but this one should be as fine
    QDoubleValidator* mf_validator;
    QDoubleValidator* cf_validator;
    QDoubleValidator* fd_validator;
    QDoubleValidator* sf_validator;


    // buttons
    QPushButton reset_button = QPushButton(tr("RESET"));

    LFMSettings check_settings(bool& ok);
    void notify_input_invalid(QString msg, QString title);
public:
    LFMSettingsWidget(QWidget *parent = nullptr);

signals:
    void new_data_sent(LFMSettings settings);

private slots:
    void process_reset();
};

#endif // LFMSETTINGS_H
