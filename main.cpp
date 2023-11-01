#include "mainwindow.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Controller ctrl;

    QObject::connect( &w, &MainWindow::dotRequested, &ctrl, &Controller::dotRequested );
    QObject::connect( &w, &MainWindow::plotReset, &ctrl, &Controller::resetRequested );
    QObject::connect( &w, &MainWindow::plotSaved, &ctrl, &Controller::saveRequested );

    QObject::connect( &ctrl, &Controller::dotSent, &w, &MainWindow::appendDot );
    QObject::connect( &ctrl, &Controller::resultSent, &w, &MainWindow::saveData );
    QObject::connect( &ctrl, &Controller::errorSent, &w, &MainWindow::setError );

    w.show();
    return a.exec();
}
