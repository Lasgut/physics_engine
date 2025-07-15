#ifndef DATAPLOTTER_H
#define DATAPLOTTER_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <Eigen/Dense>

#include "MainWindow.h"

class DataPlotter 
    : public QWidget
{
    Q_OBJECT

public:
    explicit DataPlotter(QWidget *parent = nullptr);

public slots:
    void entityKinematicsUpdated(int entityId, Eigen::Vector3d position, Eigen::Quaterniond orientation);

private:
    void newData(const double x, const double y);

    MainWindow  *window_;

    QLineSeries *dataSeries_;
    QChart      *chart_;
    QChartView  *chartView_;
};

#endif // DATAPLOTTER_H
