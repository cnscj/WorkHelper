#include "Modules/uimodules.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SMainWidget w;
    w.show();

    return a.exec();
}
