#include "controller.h"
#include "dotgenerator.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    // Инициализация объекта генерирующего точки и перенос его в отдельный поток
    DotGenerator *dg = new DotGenerator;
    dg->moveToThread( &m_dotGenerationThread );

    connect( &m_dotGenerationThread, &QThread::finished, dg, &DotGenerator::deleteLater );
    connect( this, &Controller::dotRequested, dg, &DotGenerator::generateDot );
    connect( this, &Controller::resetRequested, dg, &DotGenerator::clearData );
    connect( this, &Controller::saveRequested, dg, &DotGenerator::requestData );

    connect( dg, &DotGenerator::sendDot, this, &Controller::dotSent );
    connect( dg, &DotGenerator::sendResult, this, &Controller::resultSent );
    connect( dg, &DotGenerator::sendError, this, &Controller::errorSent );

    m_dotGenerationThread.start();
}

Controller::~Controller()
{
    m_dotGenerationThread.quit();
    m_dotGenerationThread.wait();
}
