#define CHART_WIDGET_H
#ifdef CHART_WIDGET_H

#pragma once

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

class ChartWidget
{
    public:
        ChartWidget();

        QChartView*               getChartView() { return chartView_; }
        QChart*                   getChart()     { return chart_; }
        std::vector<QLineSeries*> getData()      { return data_; }

        void addLineSeries(int r=0, int g=200, int b=255);

    private:
        void createDummyData();

        std::vector<QLineSeries*> data_;
        QChart*                   chart_;
        QChartView*               chartView_;

        QValueAxis* axisX_;
        QValueAxis* axisY_;
};

#endif
