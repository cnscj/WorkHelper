#include "Modules/uimodules.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::setOrganizationName("MySoft");
//    QCoreApplication::setOrganizationDomain("mysoft.com");
//    QCoreApplication::setApplicationName("Star Runner");
    SMainWidget w;
    w.show();

    return a.exec();
}
