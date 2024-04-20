
#include "lfmwidget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LFMWidget w;
    w.show();
    return a.exec();
}
