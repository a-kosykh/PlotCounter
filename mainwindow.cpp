#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "defs.h"

#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_chart = new QChart;
    m_lineSeries = new QLineSeries;

    setWindowTitle( mainWindowTitle );

    // Инициализация осей Х и Y
    m_xAxis = new QValueAxis;
    m_xAxis->setMax( minXAxisValue );
    m_xAxis->setLabelFormat( "%.f" );
    m_xAxis->setTitleText( xAxisTitle );
    m_chart->addAxis( m_xAxis, Qt::AlignBottom );

    QValueAxis* yAxis = new QValueAxis;
    yAxis->setMax( Defs::maxValue );
    yAxis->setLabelFormat( "%.f" );
    yAxis->setTitleText( yAxisTitle );
    m_chart->addAxis( yAxis, Qt::AlignLeft );

    // Подстановка объектов в виджет
    m_chart->legend()->setVisible( false );
    m_chart->addSeries( m_lineSeries );
    m_lineSeries->attachAxis( m_xAxis );
    m_lineSeries->attachAxis( yAxis );
    ui->chartView->setChart( m_chart );
    ui->chartView->setRenderHints( QPainter::Antialiasing );

    // Инициализация таблицы с результатами
    m_resultsTw = new QTableWidget;
    m_resultsTw->verticalHeader()->setVisible( false );
    m_resultsTw->setColumnCount( 3 );
    m_resultsTw->setHorizontalHeaderLabels( resultTWColumnNames );
    m_resultsTw->setColumnWidth( eResultsTableViewColumns::Number, ui->scrollArea->maximumWidth() / 6 );
    m_resultsTw->setColumnWidth( eResultsTableViewColumns::Count, ui->scrollArea->maximumWidth() / 3 );
    m_resultsTw->horizontalHeader()->setStretchLastSection( true );
    m_resultsTw->horizontalHeader()->setSectionsClickable( false );
    m_resultsTw->horizontalHeader()->setSectionsMovable( false );
    m_resultsTw->horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    ui->scrollArea->setWidget( m_resultsTw );

    // Инициализация соединений для контроля состояния кнопок
    connect( this, &MainWindow::stateChanged, this, &MainWindow::changeStartStopButtonTitle );
    connect( this, &MainWindow::stateChanged, this, &MainWindow::changeSaveButtonEnabled );
    connect( this, &MainWindow::stateChanged, this, &MainWindow::changeStartStopButtonEnabled );
    connect( this, &MainWindow::stateChanged, this, &MainWindow::changeResetButtonEnabled );

    ui->clearButton->setEnabled( false );
    ui->saveButton->setEnabled( false );
    ui->resetButton->setEnabled( false );
    setState( ePlotState::EmptyPlot );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendDot(int x, int y)
{
    if ( getState() == ePlotState::Reset ) {
        setState( ePlotState::EmptyPlot );
        return;
    }
    if ( getState() == ePlotState::Pause ) {
        return;
    }
    setState( ePlotState::Running );

    m_lineSeries->append( x, y );
    m_xAxis->setMax( x++ );

    emit dotRequested();
}

void MainWindow::saveResults(int count, int sum)
{
    int rowIdx = m_resultsTw->rowCount();
    if ( rowIdx >= maxResultRowCount ) {
        ui->saveButton->setEnabled( false );
        return;
    }

    m_resultsTw->insertRow( rowIdx );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Number, new QTableWidgetItem( QString::number( rowIdx + 1 ) ) );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Count, new QTableWidgetItem( QString::number( count ) ) );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Sum, new QTableWidgetItem( QString::number( sum ) ) );
    ui->clearButton->setEnabled( true );
}

void MainWindow::setError()
{
    setState( ePlotState::Error );
}

void MainWindow::setState(ePlotState state)
{
    if ( m_state == state ) {
        return;
    }

    m_state = state;
    emit stateChanged();
}

MainWindow::ePlotState MainWindow::getState() const
{
    return m_state;
}

void MainWindow::on_startStopButton_clicked()
{
    if ( m_state == ePlotState::Running ) {
        setState( ePlotState::Pause );
        return;
    }

    setState( ePlotState::Running );
    emit dotRequested();
}

void MainWindow::on_resetButton_clicked()
{
    setState( ePlotState::Reset );
    m_lineSeries->clear();
    m_xAxis->setMax( minXAxisValue );
    emit plotReset();
}


void MainWindow::on_saveButton_clicked()
{
    emit plotSaved();
}

void MainWindow::on_clearButton_clicked()
{
    m_resultsTw->clearContents();
    m_resultsTw->setRowCount( 0 );
    ui->clearButton->setEnabled( false );
}

void MainWindow::changeStartStopButtonTitle()
{
    if ( getState() == ePlotState::Running ) {
        ui->startStopButton->setText( "Stop" );
    } else {
        ui->startStopButton->setText( "Start" );
    }
}

void MainWindow::changeStartStopButtonEnabled()
{
    if ( getState() == ePlotState::Error ) {
        ui->startStopButton->setEnabled( false );
    } else {
        ui->startStopButton->setEnabled( true );
    }
}

void MainWindow::changeSaveButtonEnabled()
{
    if ( getState() == ePlotState::EmptyPlot
        || getState() == ePlotState::Reset
        || m_resultsTw->rowCount() >= maxResultRowCount ) {
        ui->saveButton->setEnabled( false );
    } else {
        ui->saveButton->setEnabled( true );
    }
}

void MainWindow::changeResetButtonEnabled()
{
    if ( getState() == ePlotState::EmptyPlot || getState() == ePlotState::Reset ) {
        ui->resetButton->setEnabled( false );
    } else {
        ui->resetButton->setEnabled( true );
    }
}

