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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    const QString startButtonTitle = "Start";
    const QString stopButtonTitle = "Stop";
    const QString xAxisTitle = "Count";
    const QString yAxisTitle = "Value";

    const int minXAxisValue = 5;

    enum ePlotState {
        EmptyPlot,
        Running,
        Reset,
        Pause,
        Error
    };

    enum eResultsTableViewColumns {
        Number,
        Count,
        Sum
    };
    const QStringList resultTWColumnNames = { "№", "Count", "Summary" };

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    void appendDot( int x, int y );
    void saveData( int count, int sum );
    void setError();

    void setState( ePlotState state );
    ePlotState getState() const;

signals:
    void dotRequested();
    void plotReset();
    void plotSaved();

    void stateChanged();

private slots:
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
    void changeStartStopButtonTitle();
    void changeStartStopButtonEnabled();
    void changeSaveButtonEnabled();
};
#endif // MAINWINDOW_H
