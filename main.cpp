#include "mapdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapData w;
    w.show();

    return a.exec();
}
