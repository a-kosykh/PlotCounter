#include "dotgenerator.h"

#include <QRandomGenerator>

DotGenerator::DotGenerator(QObject *parent)
    : QObject{parent} {}

void DotGenerator::generateDot()
{
    m_dotCount++;
    int dotY = QRandomGenerator::global()->generate() % 100;
    m_dotSum += dotY;
    emit dotGenerated( m_dotCount, dotY );
}

void DotGenerator::clearData()
{
    m_dotCount = 0;
    m_dotSum = 0;
}

void DotGenerator::requestData()
{
    emit dataSend( m_dotCount, m_dotSum );
}
