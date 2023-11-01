#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QObject>

/**
 * @brief Класс-контроллер, необходимый для связи объекта основного окна и объекта, генерирующий точки в отдельном потоке
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller( QObject *parent = nullptr );
    ~Controller();

signals:
    /**
     * @brief dotRequested Сигнал запроса новой точки
     */
    void dotRequested();
    /**
     * @brief resetRequested Сигнал, сообщающий о сбросе данных
     */
    void resetRequested();
    /**
     * @brief saveRequested Сигнал, сообщающий о сохранении результатов
     */
    void saveRequested();

    /**
     * @brief dotSent Сигнал с данными о новой точки
     * @param x Координата X
     * @param y Координата Y
     */
    void dotSent( int x, int y );

    /**
     * @brief resultSent Сигнал с результатами по графику
     * @param count Количество точек
     * @param sum Сумма значений
     */
    void resultSent( int count, int sum );
    /**
     * @brief errorSent Сигнал, сообщающий об ошибке при генерации
     */
    void errorSent();

private:
    QThread m_dotGenerationThread;
};

#endif // CONTROLLER_H
