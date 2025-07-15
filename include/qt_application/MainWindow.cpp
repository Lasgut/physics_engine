#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    ui_->CameraModeBox->addItem("Spherical");
    ui_->CameraModeBox->addItem("First Person");
    ui_->CameraModeBox->addItem("Third Person");



    rollData_  = new QLineSeries();
    rollChart_ = new QChart();

    rollChart_->legend()->hide();
    rollChart_->addSeries(rollData_);
    rollChart_->createDefaultAxes();
    rollChart_->axes(Qt::Vertical).first()->setRange(-3, 3);
    rollChart_->setVisible(true);

    rollChartView_ = new QChartView(rollChart_);
    rollChartView_->setRenderHint(QPainter::Antialiasing);
    rollChartView_->setVisible(true);

    ui_->gridLayout_data->addWidget(rollChartView_, 0, 0, 1, 1);
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void
MainWindow::setVisualizerWidget(QWidget *widget)
{
    ui_->gridLayout_visualizer->addWidget(widget, 0, 0, 1, 1);
}


QWidget*
MainWindow::getPlayButton()
{
    return ui_->PlayButton;
}


QWidget*
MainWindow::getCameraModeBox()
{
    return ui_->CameraModeBox;
}


QLineSeries*
MainWindow::getRollData()
{
    return rollData_;
}


QChart*
MainWindow::getRollChart()
{
    return rollChart_;
}
