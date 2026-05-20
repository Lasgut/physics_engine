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

    //autopilotWidget_ = new AutopilotWidget(ui_);

    setupCameraModeBox();

    for (int i = 0; i < 4; ++i)
    {
        chartWidgets_.emplace_back(new ChartWidget());
    }
    ui_->gridLayout_data_0->addWidget(chartWidgets_[0]->getChartView(), 0, 0, 1, 1);
    ui_->gridLayout_data_1->addWidget(chartWidgets_[1]->getChartView(), 0, 0, 1, 1);
    ui_->gridLayout_data_2->addWidget(chartWidgets_[2]->getChartView(), 0, 0, 1, 1);
    ui_->gridLayout_data_3->addWidget(chartWidgets_[3]->getChartView(), 0, 0, 1, 1);
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


std::vector<ChartWidget*> 
MainWindow::getChartWidgets()
{
    return chartWidgets_;
}


void
MainWindow::setupCameraModeBox()
{
    ui_->CameraModeBox->addItem("Spherical");
    ui_->CameraModeBox->addItem("First Person");
    ui_->CameraModeBox->addItem("Third Person");
}
