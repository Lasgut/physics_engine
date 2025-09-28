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

void 
PlotChart::newData(const double x, const double y, int index)
{
    auto dataSeries = chartWidget_->getData().at(index);
    auto chart      = chartWidget_->getChart();

    dataSeries->append(x, y);

    // Limit the number of points
    const int maxPoints = 200;
    while (dataSeries->count() > maxPoints) {
        dataSeries->remove(0); // Remove the oldest point
    }

    // Set span view of x-axis
    double span = 20.0;
    chart->axes(Qt::Horizontal).first()->setRange(x - span, x);

    // --- Y AXIS: auto-scale based on ALL series ---
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxY = std::numeric_limits<qreal>::lowest();

    for (auto series : chartWidget_->getData()) {
        for (const QPointF& pt : series->points()) {
            if (pt.y() < minY) minY = pt.y();
            if (pt.y() > maxY) maxY = pt.y();
        }
    }

    if (minY == std::numeric_limits<qreal>::max()) {
        minY = -1; maxY = 1; // fallback if no data
    }

    // Add margin
    qreal marginY = (maxY - minY) * 0.1;
    if (marginY == 0) marginY = 1.0;  // avoid zero span

    auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    if (axisY) {
        axisY->setRange(minY - marginY, maxY + marginY);
    }
}


void 
PlotChart::addPlotCurve()
{
    chartWidget_->addLineSeries(255, 100, 0);
}
