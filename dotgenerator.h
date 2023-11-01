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

signals:
    void sendDot( int x, int y );
    void sendResult( int count, int sum );
    void sendError();

private:
    int m_dotCount = 0;
    int m_dotSum = 0;
};

#endif // DOTGENERATOR_H
