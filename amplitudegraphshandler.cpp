
#include "amplitudegraphshandler.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <windows.h>
#include <math.h>

# define PI 3.14159265358979323846

std::mutex points_mutex;

AmplitudeGraphsHandler::AmplitudeGraphsHandler(QWidget *parent)
    : QWidget{parent}
{
    lfm_graph = new CyclicAmplitudeGraph(this);
    df_graph = new CyclicAmplitudeGraph(this);
    frame_slider = new QSlider(Qt::Horizontal, this);
    frame_slider->setSingleStep(1);
    frame_slider->setMinimum(0);
    frame_slider->setMaximum(0);

    main_layout.addWidget(lfm_graph);
    main_layout.addWidget(df_graph);
    main_layout.addWidget(frame_slider);

    setLayout(&main_layout);

    connect(this, &AmplitudeGraphsHandler::need_update, this, &AmplitudeGraphsHandler::update_graphics);
    connect(frame_slider, &QSlider::valueChanged, this, &AmplitudeGraphsHandler::process_slider);
}

AmplitudeGraphsHandler::~AmplitudeGraphsHandler()
{
    is_paused = true;
}

void AmplitudeGraphsHandler::update_graphics()
{
    df_graph->update();
    lfm_graph->update();
}

// is it safe? I bet it is not!
void AmplitudeGraphsHandler::start()
{
//    auto clock_start = std::chrono::steady_clock::now();
//    while (!is_paused){
//        auto clock_end =  std::chrono::steady_clock::now();
//        float elapsed = float(std::chrono::duration_cast<std::chrono::milliseconds>(clock_end - clock_start).count());
//        int frames = elapsed / descreet_time;
//        if (frames == 0)
//            frames = 1;

//        points_mutex.lock();
//        qDebug() << "Advanced by " << frames << " frames";
//        // lfm_graph->advance_by(frames);
//        points_mutex.unlock();

//        Sleep(50);
//        clock_start = std::chrono::steady_clock::now();

//        emit need_update();
//    }
}

void AmplitudeGraphsHandler::reset(LFMSettings settings)
{
    // linear freq changes
    qDebug() << "settings data acquired";
    QVector<QPointF> points;
    descreet_time = settings.sf * 1000.0f; // ms
    // for calc
    double period = 1.0f / settings.mf;
    int size = (period / settings.sf) + 1;
    double D = settings.fd;
    double dt = settings.sf;


    // saw, doesn't matter what exactly, only for impression of a growing freq of carrying wave
    // has to have the same amount of points for better sliding
    double dy = 0.8 * df_graph->world_size.height() / size;
    points.reserve(size);
    for (int i = 0; i < size; ++i)
    {
        double x = dt * i * settings.mf;
        double y = dy * i;
        points.emplaceBack(df_graph->get_padding().width() + x * df_graph->world_size.width() * (1 - (2.0f * df_graph->get_padding().width() / df_graph->world_size.width())),
                           df_graph->world_size.height() * (1 - (lfm_graph->get_padding().height() / lfm_graph->world_size.height())) - y);
    }

    df_graph->update_points(points);
    df_graph->update();

    // LFM
    // начальная фаза - 0
    points.clear();
    for (int i = 0; i < size; ++i)
    {
        double x = dt * i * settings.mf;
        double x_world = lfm_graph->get_padding().width() + x * lfm_graph->world_size.width() * (1 - (2.0f * lfm_graph->get_padding().width() / lfm_graph->world_size.width()));
        double y = cos(PI / 2.0f + 2.0f * PI * (settings.cf * x + (D * 2.0f / period) * x * x));
        double y_world = lfm_graph->world_size.height() / 2.0f + y * lfm_graph->world_size.height() * (1 - (2.0f * lfm_graph->get_padding().height() / lfm_graph->world_size.height())) / 2.0f;
        if (x_world > lfm_graph->world_size.width() - lfm_graph->get_padding().width())
            break;

        points.emplace_back(x_world, y_world);
    }

    lfm_graph->update_points(points);
    lfm_graph->update();

    frame_slider->setMaximum(size + 1);
    frame_slider->setValue(0);

    std::thread t(&AmplitudeGraphsHandler::start, this);
    t.detach();
}

void AmplitudeGraphsHandler::process_slider(int val)
{
    int diff = (val - frame_value);
    if (diff < 0)
        diff = frame_slider->maximum() + diff;

    frame_value = val;
    points_mutex.lock();
    df_graph->advance_by(diff);
    df_graph->update();
    lfm_graph->advance_by(diff);
    lfm_graph->update();
    points_mutex.unlock();
}

