#include <QApplication>

#include "viewer.h"
#include "../Logic/Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my::Model m;
    my::Controller c(&m);
    Viewer w(&c);
    w.show();
    return a.exec();
}
