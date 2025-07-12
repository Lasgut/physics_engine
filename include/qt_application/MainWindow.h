#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

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

    QLineSeries* getRollData();
    QChart* getRollChart();

private:
    Ui::MainWindow *ui_;

    QLineSeries* rollData_;
    QChart*      rollChart_;
    QChartView*  rollChartView_;
};
#endif // MAINWINDOW_H
