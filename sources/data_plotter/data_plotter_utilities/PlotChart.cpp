#include "PlotChart.h"
#include "KinematicsLib.h"
#include "ChartWidget.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

PlotChart::PlotChart(ChartWidget* chartWidget)
    : chartWidget_(chartWidget)
{
}

void PlotChart::newData(const double x, const double y)
{
    using namespace Lib::Kinematics::Utils;

    auto dataSeries = chartWidget_->getData();
    auto chart      = chartWidget_->getChart();
    auto chartView  = chartWidget_->getChartView();

    double xSec = x / 1e9;
    double yDeg = rad2deg(y);
    dataSeries->append(xSec, yDeg);

    // Limit the number of points
    const int maxPoints = 2000;
    while (dataSeries->count() > maxPoints) {
        dataSeries->remove(0); // Remove the oldest point
    }

    // Dynamically adjust axes
    qreal minX = dataSeries->at(0).x();
    qreal maxX = dataSeries->at(0).x();
    qreal minY = dataSeries->at(0).y();
    qreal maxY = dataSeries->at(0).y();

    for (int i = 1; i < dataSeries->count(); ++i) {
        const QPointF& pt = dataSeries->at(i);
        if (pt.x() < minX) minX = pt.x();
        if (pt.x() > maxX) maxX = pt.x();
        if (pt.y() < minY) minY = pt.y();
        if (pt.y() > maxY) maxY = pt.y();
    }

    // Add some margin
    qreal marginX = (maxX - minX) * 0.05;
    qreal marginY = (maxY - minY) * 0.05;

    chart->axes(Qt::Horizontal).first()->setRange(minX - marginX, maxX + marginX);
    chart->axes(Qt::Vertical).first()->setRange(minY - marginY, maxY + marginY);
    chart->setTitle("Roll");
}