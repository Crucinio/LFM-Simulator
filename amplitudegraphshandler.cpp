
#include "amplitudegraphshandler.h"

#include <math.h>

# define PI 3.14159265358979323846

void GraphHandler::fill_points_time_domain(QVector<QPointF> &points, double period, double sampling_frequency, double carrier_frequency, double deviation)
{
    points.clear();
    int samples_number = std::ceil(period * sampling_frequency);
    points.reserve(samples_number);

    double dt = period / samples_number;
    for (int i = 0; i < samples_number; ++i)
    {
        double t = dt * i;
        double y = cos(PI / 2.0f + 2.0f * PI * ((carrier_frequency - deviation) * t + deviation * t * ( t / period)));
        points.emplace_back(float(i) / samples_number, y);
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

void GraphHandler::fill_points_frequency_domain(QVector<QPointF> &points_container, const QVector<QPointF> &time_domain_points)
{
    points_container.clear();
    points_container.reserve(time_domain_points.size());
    for (int k = 0; k < time_domain_points.size(); ++k)
    {
        double imaginary = calculate_imaginary_part(time_domain_points, k);
        double real = calculate_real_part(time_domain_points, k);
        double R = sqrtf(real * real + imaginary * imaginary);
        points_container.emplace_back(time_domain_points[k].x(), -R);
    }
}

GraphHandler::GraphHandler(QWidget *parent) : QTabWidget{parent}
{
    // initialisation of lfm graph in time domain
    lfm_time_graph = new Graph(this);
    lfm_time_graph->set_argument_text("t, sec");
    lfm_time_graph->set_value_text("s(t)");
    lfm_time_graph->set_amplitude(250);
    lfm_time_graph->set_amplitude_text("A");


    // initialisation of lfm graph in frequency domain
    lfm_frequency_graph = new Graph(this);
    lfm_frequency_graph->set_starting_point({40, lfm_frequency_graph->get_world_size().height() - 30});
    lfm_frequency_graph->set_amplitude(520);
    lfm_frequency_graph->set_argument_text("f, Hz");
    lfm_frequency_graph->set_value_text("s(w)");

    this->addTab(lfm_time_graph, "Time domain");
    this->addTab(lfm_frequency_graph, "Frequency domain");
}

GraphHandler::~GraphHandler()
{

}

void GraphHandler::reset(LFMSettings settings)
{
    QVector<QPointF> lfm_points;
    fill_points_time_domain(lfm_points, 1 / settings.mf, settings.sf, settings.cf, settings.fd);
    lfm_time_graph->update_points(lfm_points);

    QVector<QPointF> freq_points;
    fill_points_frequency_domain(freq_points, lfm_points);
    lfm_frequency_graph->update_points(freq_points);

    lfm_time_graph->update();
    lfm_frequency_graph->update();
}
