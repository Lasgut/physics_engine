#define CHART_WIDGET_H
#ifdef CHART_WIDGET_H

#pragma once

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

class ChartWidget
{
    public:
        ChartWidget();

        QChartView*  getChartView() { return chartView_; }
        QChart*      getChart()     { return chart_; }
        QLineSeries* getData()      { return data_; }

    private:
        void createDummyData();

        QLineSeries* data_;
        QChart*      chart_;
        QChartView*  chartView_;
};

#endif
