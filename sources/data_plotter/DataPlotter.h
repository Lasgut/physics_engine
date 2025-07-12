#ifndef DATAPLOTTER_H
#define DATAPLOTTER_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include "MainWindow.h"

class DataPlotter : public QWidget
{
    Q_OBJECT

public:
    explicit DataPlotter(QWidget *parent = nullptr);

public slots:
    void newData(const double x, const double y);


private:
    MainWindow  *window_;

    QLineSeries *dataSeries_;
    QChart      *chart_;
    QChartView  *chartView_;
};

#endif // DATAPLOTTER_H
