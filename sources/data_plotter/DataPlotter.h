#ifndef DATAPLOTTER_H
#define DATAPLOTTER_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <Eigen/Dense>
#include <vector>

#include "MainWindow.h"
#include "data_plotter_utilities/PlotChart.h"
#include "ChartWidget.h"

class DataPlotter 
    : public QWidget
{
    Q_OBJECT

public:
    explicit DataPlotter(QWidget *parent = nullptr);
    virtual ~DataPlotter();

public slots:
    void entityKinematicsUpdated(int entityId, Eigen::Vector3d position, Eigen::Quaterniond orientation);

private:
    void newData(const double x, const double y);

    MainWindow  *window_;

    std::vector<PlotChart> plotCharts_;
};

#endif // DATAPLOTTER_H
