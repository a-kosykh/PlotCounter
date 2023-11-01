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
    void dotRequested();
    void resetRequested();
    void saveRequested();

    void dotSent( int x, int y );
    void resultSent( int count, int sum );
    void errorSent();

private:
    QThread m_dotGenerationThread;
};

#endif // CONTROLLER_H
