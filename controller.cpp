#include "controller.h"
#include "dotgenerator.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    DotGenerator *dg = new DotGenerator;
    dg->moveToThread( &m_dotGenerationThread );

    connect( &m_dotGenerationThread, &QThread::finished, dg, &DotGenerator::deleteLater );
    connect( this, &Controller::dotRequested, dg, &DotGenerator::generateDot );
    connect( dg, &DotGenerator::dotGenerated, this, &Controller::dotGenerated );

    connect( this, &Controller::resetRequested, dg, &DotGenerator::clearData );

    connect( this, &Controller::saveRequested, dg, &DotGenerator::requestData );
    connect( dg, &DotGenerator::dataSend, this, &Controller::dataSend );

    m_dotGenerationThread.start();
}

Controller::~Controller()
{
    m_dotGenerationThread.quit();
    m_dotGenerationThread.wait();
}
