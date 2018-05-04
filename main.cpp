#include "connectwindow.h"
#include "mainwindow.h"
#include <QApplication>
MainWindow* mainwindow;
ConnectWindow* connectwindow;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectWindow cw;
    MainWindow mw;
    cw.show();
    mainwindow = &mw;
    connectwindow = &cw;
    return a.exec();
}
