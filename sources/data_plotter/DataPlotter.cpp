#include "DataPlotter.h"
#include "MathLib.h"
#include "MainWindow.h"
#include "Clock.h"
#include "Entity.h"

#include <iostream>
#include <Eigen/Dense>

DataPlotter::DataPlotter(QWidget *parent)
{
    window_ = static_cast<MainWindow*>(parent);

    for (auto chartWidget : window_->getChartWidgets()) 
    {
        chartWidget->getData().clear(); // clear dummy data
        plotCharts_.emplace_back(chartWidget);
    }

    plotCharts_[0].getChartWidget()->getChart()->setTitle("Roll");

    plotCharts_[1].getChartWidget()->getChart()->setTitle("Pitch");
    plotCharts_[1].addPlotCurve();

    plotCharts_[2].getChartWidget()->getChart()->setTitle("Yaw");

    plotCharts_[3].getChartWidget()->getChart()->setTitle("Altitude");
    plotCharts_[3].addPlotCurve();
}


void 
DataPlotter::updatePlots()
{
    static Clock clock("plot");
    if (!clock.rateLimit(10))
    {
        return;
    }

    plotCharts_[0].newData(roll_.first, roll_.second);

    plotCharts_[1].newData(pitch_.first, pitch_.second);
    plotCharts_[1].newData(desiredPitch_.first, desiredPitch_.second, 1);

    plotCharts_[2].newData(yaw_.first, yaw_.second);

    plotCharts_[3].newData(altitude_.first, altitude_.second);
    plotCharts_[3].newData(desiredAltitude_.first, desiredAltitude_.second, 1);
}


void 
DataPlotter::controlSystemDataUpdated(int entityId, ControlSystemData* ctrlSysData)
{
    desiredPitch_.first  = ctrlSysData->timeStamp;
    desiredPitch_.second = ctrlSysData->desiredPitch;

    desiredAltitude_.first  = ctrlSysData->timeStamp;
    desiredAltitude_.second = ctrlSysData->desiredAltitude;
}


void 
DataPlotter::entityKinematicsUpdated(int entityId, Kinematics* kinematics)
{
    using namespace Lib::Math::Utils;

    if (entityId == 1) // Assuming entityId 1 is the one we are interested in
    {
        auto time  = kinematics->getTimeStamp();

        altitude_.first  = time;
        altitude_.second = -kinematics->getPosition().z();

        auto eulerAngles = kinematics->getEulerAngles();
        roll_.first   = time;
        roll_.second  = rad2deg(eulerAngles[0]);
        pitch_.first  = time;
        pitch_.second = rad2deg(eulerAngles[1]);
        yaw_.first    = time;
        yaw_.second   = rad2deg(eulerAngles[2]);
    }
}