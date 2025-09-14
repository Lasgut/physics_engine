#define PLOT_CHART_H
#ifdef PLOT_CHART_H

#pragma once

#include <vector>

#include "ChartWidget.h"

class PlotChart
{
    public:
        PlotChart(ChartWidget* chartWidget);

        void newData(const double x, const double y);

    private:
        ChartWidget* chartWidget_;


};

#endif