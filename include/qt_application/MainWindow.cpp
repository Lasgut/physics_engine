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
    if (!widget) return;

    QWidget* placeholder = ui_->VisualizerGLWidget;
    if (!placeholder) return;

    QWidget* parentWidget = placeholder->parentWidget();
    if (!parentWidget) return;

    QLayout* layout = parentWidget->layout();
    if (!layout) return;

    layout->replaceWidget(placeholder, widget);
    placeholder->deleteLater();
    widget->show();
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
