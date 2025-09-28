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
#include "UnmannedAerialVehicle.h"

class DataPlotter 
    : public QWidget
{
    Q_OBJECT

public:
    explicit DataPlotter(QWidget *parent = nullptr);

    void updatePlots();

public slots:
    void entityKinematicsUpdated(int entityId, Kinematics* kinematics);
    void controlSystemDataUpdated(int entityId, ControlSystemData* ctrlSysData);

private:
    MainWindow  *window_;

    std::vector<PlotChart> plotCharts_;

    std::pair<double,double> roll_{0.0, 0.0};
    std::pair<double,double> pitch_{0.0, 0.0};
    std::pair<double,double> yaw_{0.0, 0.0};
    std::pair<double,double> altitude_{0.0, 0.0};
    std::pair<double,double> desiredPitch_{0.0, 0.0};
    std::pair<double,double> desiredAltitude_{0.0, 0.0};
};

#endif // DATAPLOTTER_H
