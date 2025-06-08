#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    ui_->CameraModeBox->addItem("Spherical");
    ui_->CameraModeBox->addItem("First Person");
    ui_->CameraModeBox->addItem("Third Person");
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void
MainWindow::setVisualizerWidget(QWidget *widget)
{
    ui_->VisualizerGLWidget->layout()->replaceWidget(ui_->VisualizerGLWidget, widget);
}
