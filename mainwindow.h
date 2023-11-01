#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QTableWidget>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
 * @brief Класс, описывающий графический интерфейс
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    /**
     * Строковые константы
     */
    const QString mainWindowTitle = "Plot Counter";
    const QString startButtonTitle = "Start";
    const QString stopButtonTitle = "Stop";
    const QString xAxisTitle = "Count";
    const QString yAxisTitle = "Value";

    const int minXAxisValue = 5;


    /**
     * @brief Состояния класса объекта класса ePlotState
     */
    enum ePlotState {
        EmptyPlot,
        Running,
        Reset,
        Pause,
        Error
    };

    /**
     * @brief The eResultsTableViewColumns enum Столбцы таблиц с результатами
     */
    enum eResultsTableViewColumns {
        Number,
        Count,
        Sum
    };
    const int maxResultRowCount = 65535; // Максимальное количество объектов в таблице
    const QStringList resultTWColumnNames = { "№", "Count", "Summary" };

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    /**
     * @brief appendDot Добавить точку на график
     * @param x Координата X
     * @param y Координата Y
     */
    void appendDot( int x, int y );

    /**
     * @brief saveResults Сохранить результаты
     * @param count Количество точек
     * @param sum Сумма значений
     */
    void saveResults( int count, int sum );

    /**
     * @brief setError Перевод класса в состояние ошибки
     */
    void setError();

    /**
     * @brief setState Установка состояния
     * @param state Состояние
     */
    void setState( ePlotState state );

    /**
     * @brief getState Получение текущего состояния
     * @return Состояние класса
     */
    ePlotState getState() const;

signals:
    /**
     * @brief dotRequested Сигнал запроса новой точки
     */
    void dotRequested();

    /**
     * @brief plotReset Сигнал о сбросе графика
     */
    void plotReset();

    /**
     * @brief plotSaved Сигнал о сохранении информации о графике
     */
    void plotSaved();

    /**
     * @brief stateChanged Сигнал о смене состояния
     */
    void stateChanged();

private slots:
    /**
     * Слоты на нажатие кнопок
     */
    void on_startStopButton_clicked();
    void on_resetButton_clicked();
    void on_saveButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QChart *m_chart;
    QLineSeries* m_lineSeries;
    QValueAxis* m_xAxis;
    QTableWidget* m_resultsTw;

    ePlotState m_state;

private:
    /**
     * Слоты изменение свойств кнопок при смене состояний
     */
    void changeStartStopButtonTitle();
    void changeStartStopButtonEnabled();
    void changeSaveButtonEnabled();
    void changeResetButtonEnabled();
};
#endif // MAINWINDOW_H
