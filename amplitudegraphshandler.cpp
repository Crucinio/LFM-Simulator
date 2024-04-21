
#include "amplitudegraphshandler.h"

AmplitudeGraphsHandler::AmplitudeGraphsHandler(QWidget *parent)
    : QWidget{parent}
{
    lfm_graph = new CyclicAmplitudeGraph(this);
    df_graph = new CyclicAmplitudeGraph(this);


    main_layout.addWidget(lfm_graph);
    main_layout.addWidget(df_graph);

    setLayout(&main_layout);

    paintEvent(nullptr);
}

void AmplitudeGraphsHandler::start()
{

}

void AmplitudeGraphsHandler::reset(LFMSettings settings)
{
    qDebug() << "settings data acquired";
    QVector<QPointF> points;
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
}

