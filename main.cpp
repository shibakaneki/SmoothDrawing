#include <QtGui>
#include <QApplication>

#include "MainWnd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWnd w;
    w.showMaximized();
    return a.exec();
}
