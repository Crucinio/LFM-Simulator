
#include "amplitudegraphshandler.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <windows.h>

std::mutex points_mutex;

AmplitudeGraphsHandler::AmplitudeGraphsHandler(QWidget *parent)
    : QWidget{parent}
{
    lfm_graph = new CyclicAmplitudeGraph(this);
    df_graph = new CyclicAmplitudeGraph(this);


    main_layout.addWidget(lfm_graph);
    main_layout.addWidget(df_graph);

    setLayout(&main_layout);

    connect(this, &AmplitudeGraphsHandler::need_update, this, &AmplitudeGraphsHandler::update_graphics);
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
    auto clock_start = std::chrono::steady_clock::now();
    while (!is_paused){
        auto clock_end =  std::chrono::steady_clock::now();
        float elapsed = float(std::chrono::duration_cast<std::chrono::milliseconds>(clock_end - clock_start).count());
        int frames = elapsed / descreet_time + 1;
        points_mutex.lock();
        qDebug() << "Advanced by " << frames << " frames";
        df_graph->advance_by(frames);
        points_mutex.unlock();

        Sleep(50);
        clock_start = std::chrono::steady_clock::now();

        emit need_update();
    }
}

void AmplitudeGraphsHandler::reset(LFMSettings settings)
{
    qDebug() << "settings data acquired";
    QVector<QPointF> points;
    descreet_time = settings.dt * 1000.0f; // ms
    float period = 1 / settings.mf;
    int size = (period / settings.dt) + 1;
    float D = 0.4f * df_graph->world_size.height();
    float x0 = df_graph->get_padding().width();
    float y0 = 2.0f * D + df_graph->get_padding().height();
    float dx = df_graph->world_size.width() * 0.9 / (size + 1);
    float dy = 2.0f * D / (size + 1);


    for (int i = 0; i < size + 1; ++i)
    {
        points.emplaceBack(x0 + dx * i, y0 - dy * i);
    }

    df_graph->update_points(points);
    df_graph->advance_by(points.size() / 2);
    df_graph->update();

    std::thread t(&AmplitudeGraphsHandler::start, this);
    t.detach();
}

