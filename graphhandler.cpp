
#include "graphhandler.h"

#include <math.h>

# define PI 3.14159265358979323846

void GraphHandler::fill_points_time_domain(QVector<QPointF> &points, double period, double sampling_frequency, double carrier_frequency, double deviation)
{
    points.clear();
    int samples_number = std::ceil(period * sampling_frequency);
    points.reserve(samples_number + 1);

    double dt = period / samples_number;
    for (int i = 0; i < samples_number + 1; ++i)
    {
        double t = dt * i;
        double y = cos(-PI / 2.0f + 2.0f * PI * ((carrier_frequency - deviation) * t + deviation * t * ( t / period)));
        points.emplace_back(i, y);
    }
}

double GraphHandler::calculate_imaginary_part(const QVector<QPointF> &time_domain_points, int k)
{
    double S = 0;
    for (int n = 0; n < time_domain_points.size(); ++n)
    {
        S += time_domain_points[n].y() * sin((2.0f * PI * k * n) / time_domain_points.size());
    }

    return -S;
}

double GraphHandler::calculate_real_part(const QVector<QPointF> &time_domain_points, int k)
{
    double S = 0;
    for (int n = 0; n < time_domain_points.size(); ++n)
    {
        S += time_domain_points[n].y() * cos((2.0f * PI * k * n) / time_domain_points.size());
    }

    return S;
}

void GraphHandler::fill_points_frequency_domain(QVector<QPointF> &points_container, const QVector<QPointF> &time_domain_points, double boundary)
{
    // we are interested only with the frequencies that lie between Fmin and Fmax obviously
    points_container.clear();
    points_container.reserve(time_domain_points.size());
    double R_max = 0;
    int i = -boundary / 2;
    for (int k = 0; k < boundary; ++k, ++i)
    {
        double imaginary = calculate_imaginary_part(time_domain_points, k);
        double real = calculate_real_part(time_domain_points, k);
        double R = sqrtf(real * real + imaginary * imaginary) / time_domain_points.size();
        if (R > R_max)
            R_max = R;

        points_container.emplace_back(i, R);
    }
}

GraphHandler::GraphHandler(QWidget *parent) : QTabWidget{parent}
{
    // initialisation of lfm graph in time domain
    lfm_time_graph = new Graph(this);
    lfm_time_graph->set_argument_text("t, sec");
    lfm_time_graph->set_value_text("s(t)");
    lfm_time_graph->set_graph_size({720, 250});
    lfm_time_graph->set_amplitude(250);
    lfm_time_graph->set_amplitude_text("1");

    // initialisation of lfm graph in frequency domain
    lfm_frequency_graph = new Graph(this);
    lfm_frequency_graph->set_starting_point({350, lfm_frequency_graph->get_world_size().height() - 30});
    lfm_frequency_graph->set_graph_size({600, 500});
    lfm_frequency_graph->set_amplitude(500);
    lfm_frequency_graph->set_argument_text("f, Hz");
    lfm_frequency_graph->set_value_text("s(w)");

    int m = 6;
    QVector<std::pair<double, QString> > marks_y(m);
    for (int i = 0; i < m; ++i)
    {
        marks_y[i] = {float(i) / float(m), QString::number(float(i) / float(m - 1), 'g', 2)};
    }
    lfm_frequency_graph->set_special_marks_y(marks_y);

    this->addTab(lfm_time_graph, "Time domain");
    this->addTab(lfm_frequency_graph, "Frequency domain");
}

GraphHandler::~GraphHandler()
{

}

void GraphHandler::reset(LFMSettings settings)
{
    // time domain
    QVector<QPointF> lfm_points;
    fill_points_time_domain(lfm_points, 1 / settings.mf, settings.sf, settings.cf, settings.fd);
    lfm_time_graph->update_points(lfm_points);

    // frequency domain
    QVector<QPointF> freq_points;
    fill_points_frequency_domain(freq_points, lfm_points, (2.0 * settings.cf) / settings.mf);

    // x marks
    QVector<std::pair<int, QString> > marks_x(2);
    marks_x[0] = {(settings.cf - settings.fd) / settings.mf, QString::number(settings.cf - settings.fd) + "Hz"};
    marks_x[1] = {freq_points.size() - (settings.cf - settings.fd) / settings.mf, QString::number(settings.fd + settings.cf) + "Hz"};
    lfm_frequency_graph->set_special_marks_x(marks_x);

    // y marks
    double max_R = 0;
    for (auto& p : freq_points)
    {
        if (p.y() > max_R)
            max_R = p.y();
    }

    for (auto& p : freq_points)
    {
        p.setY(p.y() / max_R);
    }
    lfm_frequency_graph->update_points(freq_points);

    lfm_time_graph->update();
    lfm_frequency_graph->update();
}
