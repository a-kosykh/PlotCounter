#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller( QObject *parent = nullptr );
    ~Controller();

signals:
    void dotGenerated( int x, int y );
    void dotRequested();
    void resetRequested();
    void saveRequested();
    void dataSend( int count, int sum );

private:
    QThread m_dotGenerationThread;
};

#endif // CONTROLLER_H
