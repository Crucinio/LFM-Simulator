
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
        points.emplace_back(i / samples_number, y);
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
    QVector<QPointF> points;
    lfm_time_graph->set_x_multiplier(settings.mf);
    fill_points_time_domain(points, 1 / settings.mf, settings.sf, settings.cf, settings.fd);

    lfm_time_graph->update_points(points);
    lfm_time_graph->update();

//    frame_slider->setMaximum(size + 1);
//    frame_slider->setValue(0);
}
