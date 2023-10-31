#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H

#include <QObject>

class DotGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DotGenerator( QObject *parent = nullptr );
    void generateDot();
    void clearData();
    void requestData();

private:
    int m_dotCount = 0;
    int m_dotSum = 0;

signals:
    void dotGenerated( int x, int y );
    void dataSend( int count, int sum );
};

#endif // DOTGENERATOR_H
