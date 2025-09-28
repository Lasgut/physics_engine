#define PLOT_CHART_H
#ifdef PLOT_CHART_H

#pragma once

#include <vector>

#include "ChartWidget.h"

class PlotChart
{
    public:
        PlotChart(ChartWidget* chartWidget);

        void newData(const double x, const double y, int index=0);
        void addPlotCurve();

        ChartWidget* getChartWidget() { return chartWidget_; }

    private:
        ChartWidget* chartWidget_;


};

#endif