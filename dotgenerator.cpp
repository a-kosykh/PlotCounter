#include "dotgenerator.h"
#include "defs.h"

#include <QRandomGenerator>

#include <limits>

DotGenerator::DotGenerator(QObject *parent)
    : QObject{parent} {}

void DotGenerator::generateDot()
{
    if ( m_dotCount == std::numeric_limits<int>::max() ) {
        emit sendError();
        return;
    }

    if ( std::numeric_limits<int>::max() - m_dotSum < Defs::maxValue ) {
        emit sendError();
        return;
    }

    m_dotCount++;
    int dotY = QRandomGenerator::global()->generate() % Defs::maxValue;
    m_dotSum += dotY;
    emit sendDot( m_dotCount, dotY );
}

void DotGenerator::clearData()
{
    m_dotCount = 0;
    m_dotSum = 0;
}

void DotGenerator::requestData()
{
    emit sendResult( m_dotCount, m_dotSum );
}
