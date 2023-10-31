#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    m_xAxis = new QValueAxis;
    m_xAxis->setMax( 5 );
    m_xAxis->setLabelFormat( "%.f" );
    m_xAxis->setTitleText( "Count" );
    m_chart->addAxis( m_xAxis, Qt::AlignBottom );

    QValueAxis* yAxis = new QValueAxis;
    yAxis->setMax( 100 );
    yAxis->setLabelFormat( "%.f" );
    yAxis->setTitleText( "Value" );
    m_chart->addAxis( yAxis, Qt::AlignLeft );

    m_resultsTw = new QTableWidget;
    m_resultsTw->verticalHeader()->setVisible( false );
    m_resultsTw->setColumnCount( 3 );
    m_resultsTw->setHorizontalHeaderLabels( QStringList() << "№" << "Count" << "Summary" );
    m_resultsTw->setColumnWidth( eResultsTableViewColumns::Number, ui->scrollArea->maximumWidth() / 6 );
    m_resultsTw->setColumnWidth( eResultsTableViewColumns::Count, ui->scrollArea->maximumWidth() / 3 );
    m_resultsTw->horizontalHeader()->setStretchLastSection( true );
    m_resultsTw->horizontalHeader()->setSectionsClickable( false );
    m_resultsTw->horizontalHeader()->setSectionsMovable( false );
    m_resultsTw->horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );

    m_chart->legend()->setVisible( false );
    m_chart->addSeries( m_lineSeries );
    m_lineSeries->attachAxis( m_xAxis );
    m_lineSeries->attachAxis( yAxis );
    ui->chartView->setChart( m_chart );
    ui->chartView->setRenderHints( QPainter::Antialiasing );

    ui->scrollArea->setWidget( m_resultsTw );

    setState( ePlotState::EmptyPlot );
    connect( this, &MainWindow::stateChanged, this, &MainWindow::changeStartStopButtonTitle );
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
    if ( getState() ==  ePlotState::Pause ) {
        return;
    }
    setState( ePlotState::Running );

    m_lineSeries->append( x, y );
    m_xAxis->setMax( x++ );

    requestDot();
}

void MainWindow::requestDot()
{
    emit dotRequested();
}

void MainWindow::resetPlot()
{
    m_lineSeries->clear();
    m_xAxis->setMax( 5 );
}

void MainWindow::saveData(int count, int sum)
{
    int rowIdx = m_resultsTw->rowCount();
    m_resultsTw->insertRow( rowIdx );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Number, new QTableWidgetItem( QString::number( rowIdx + 1 ) ) );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Count, new QTableWidgetItem( QString::number( count ) ) );
    m_resultsTw->setItem( rowIdx, eResultsTableViewColumns::Sum, new QTableWidgetItem( QString::number( sum ) ) );
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
    requestDot();
}

void MainWindow::on_resetButton_clicked()
{
    setState( ePlotState::Reset );
    resetPlot();
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
}

void MainWindow::changeStartStopButtonTitle()
{
    if ( getState() == ePlotState::Running ) {
        ui->startStopButton->setText( "Stop" );
    }
    else {
        ui->startStopButton->setText( "Start" );
    }
}

