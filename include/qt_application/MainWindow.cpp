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

    // Get the parent widget and layout of the placeholder openGLWidget
    QWidget* placeholder = ui_->VisualizerGLWidget;
    if (!placeholder) return;

    QWidget* parentWidget = placeholder->parentWidget();
    if (!parentWidget) return;

    QLayout* layout = parentWidget->layout();
    if (!layout) return;

    // Replace the placeholder widget with the new widget
    layout->replaceWidget(placeholder, widget);

    // Hide and optionally delete the placeholder widget
    placeholder->hide();
    // placeholder->deleteLater();  // Optional if you want to delete it

    // Show the new widget explicitly
    widget->show();
}
