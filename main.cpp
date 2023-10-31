#include "mainwindow.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller ctrl;

    QObject::connect( &ctrl, &Controller::dotGenerated, &w, &MainWindow::appendDot );
    QObject::connect( &w, &MainWindow::dotRequested, &ctrl, &Controller::dotRequested );
    QObject::connect( &w, &MainWindow::plotReset, &ctrl, &Controller::resetRequested );
    QObject::connect( &w, &MainWindow::plotSaved, &ctrl, &Controller::saveRequested );
    QObject::connect( &ctrl, &Controller::dataSend, &w, &MainWindow::saveData );

    w.show();
    return a.exec();
}
