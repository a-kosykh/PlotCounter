#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H

#include <QObject>
/**
 * @brief Класс, генерирующий точки в отдельном потоке
 */
class DotGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DotGenerator( QObject *parent = nullptr );
    /**
     * @brief generateDot Генерация новой точки
     */
    void generateDot();
    /**
     * @brief clearData Очистка данных
     */
    void clearData();
    /**
     * @brief requestData Запрос результата
     */
    void requestData();

signals:
    /**
     * @brief sendDot Сигнал, сообщающий о генерации новой точки
     * @param x Координата X
     * @param y Координата Y
     */
    void sendDot( int x, int y );

    /**
     * @brief sendResult Сигнал с результатами
     * @param count Количество точек
     * @param sum Сумма значений
     */
    void sendResult( int count, int sum );

    /**
     * @brief sendError Отправка ошибки
     */
    void sendError();

private:
    /**
     * @brief m_dotCount Текущее количество точек
     */
    int m_dotCount = 0;

    /**
     * @brief m_dotSum Текущая сумма значений
     */
    int m_dotSum = 0;
};

#endif // DOTGENERATOR_H
