#include "DataPlotter.h"
#include "KinematicsLib.h"
#include "MainWindow.h"

#include <iostream>
#include <Eigen/Dense>

DataPlotter::DataPlotter(QWidget *parent)
{
    window_ = static_cast<MainWindow*>(parent);

    for (auto chartWidget : window_->getChartWidgets()) 
    {
        plotCharts_.emplace_back(chartWidget);
    }
}

DataPlotter::~DataPlotter()
{
}

void 
DataPlotter::entityKinematicsUpdated(int entityId, Eigen::Vector3d position, Eigen::Quaterniond orientation)
{
    if (entityId == 1) // Assuming entityId 1 is the one we are interested in
    {
        // Convert position and orientation to the format needed for plotting
        double x = std::chrono::steady_clock::now().time_since_epoch().count();
        double y = Lib::Kinematics::Utils::quat2euler(orientation).x();

        plotCharts_[0].newData(x, y);
    }
}