#include "DataPlotter.h"
#include "KinematicsLib.h"

#include <iostream>

DataPlotter::DataPlotter(QWidget *parent)
{
    window_ = static_cast<MainWindow*>(parent);

    dataSeries_ = window_->getRollData();
    chart_      = window_->getRollChart();
}


void
DataPlotter::newData(const double x, const double y)
{
    using namespace Lib::Kinematics::Utils;

    double xSec = x / 1e9;
    double yDeg = rad2deg(y);
    dataSeries_->append(xSec, yDeg);

    // Limit the number of points
    const int maxPoints = 1000;
    while (dataSeries_->count() > maxPoints) {
        dataSeries_->remove(0); // Remove the oldest point
    }

    // Dynamically adjust axes
    qreal minX = dataSeries_->at(0).x();
    qreal maxX = dataSeries_->at(0).x();
    qreal minY = dataSeries_->at(0).y();
    qreal maxY = dataSeries_->at(0).y();

    for (int i = 1; i < dataSeries_->count(); ++i) {
        const QPointF& pt = dataSeries_->at(i);
        if (pt.x() < minX) minX = pt.x();
        if (pt.x() > maxX) maxX = pt.x();
        if (pt.y() < minY) minY = pt.y();
        if (pt.y() > maxY) maxY = pt.y();
    }

    // Add some margin
    qreal marginX = (maxX - minX) * 0.05;
    qreal marginY = (maxY - minY) * 0.05;

    chart_->axes(Qt::Horizontal).first()->setRange(minX - marginX, maxX + marginX);
    //chart_->axes(Qt::Vertical).first()->setRange(minY - marginY, maxY + marginY);
}