#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setApplicationName("qbarmanager");
    QCoreApplication::setApplicationVersion("0.0.1");
    MainWindow w;
    w.show();
    
    return a.exec();
}
