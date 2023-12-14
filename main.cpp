#include "mainwindow.h"
#include "dota2mapmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Dota2MapManager::getInstance().init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
