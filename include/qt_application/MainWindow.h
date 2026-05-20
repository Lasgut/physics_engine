#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AutopilotWidget.h"
#include "ChartWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setVisualizerWidget(QWidget* widget);

    QWidget* getPlayButton();
    QWidget* getCameraModeBox();

    std::vector<ChartWidget*> getChartWidgets();

private:
    void setupCameraModeBox();

    Ui::MainWindow* ui_;

    std::vector<ChartWidget*> chartWidgets_;
    //AutopilotWidget*          autopilotWidget_;
};
#endif // MAINWINDOW_H
