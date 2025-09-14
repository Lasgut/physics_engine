#include "ChartWidget.h"
#include <QtCharts/QValueAxis>

ChartWidget::ChartWidget()
{
    data_  = new QLineSeries();
    data_->setPen(QPen(QColor(0, 200, 255), 1)); // Thin line

    chart_ = new QChart();
    chart_->legend()->hide();
    chart_->addSeries(data_);
    chart_->setVisible(true);
    chart_->setTitle("TITLE");
    chart_->setTitleFont(QFont("Roboto Mono", 8, QFont::Bold));
    chart_->setTitleBrush(QBrush(QColor(255, 255, 255)));
    chart_->setBackgroundBrush(QBrush(QColor(60, 60, 60)));
    chart_->setMargins(QMargins(0,0,0,0)); 

    // Custom X axis
    auto axisX = new QValueAxis;
    axisX->setRange(0, 4);
    axisX->setTickCount(9); // Matches your range and grid style
    axisX->setTitleText("X-AXIS");
    axisX->setTitleFont(QFont("Inconsolata", 6));
    axisX->setTitleBrush(QBrush(QColor(255, 255, 255)));
    axisX->setLabelsFont(QFont("Inconsolata", 6));
    axisX->setLabelsBrush(QBrush(QColor(255, 255, 255)));

    chart_->addAxis(axisX, Qt::AlignBottom);
    data_->attachAxis(axisX);

    // Custom Y axis
    auto axisY = new QValueAxis;
    axisY->setRange(0, 4);
    axisY->setTickCount(9);
    axisY->setTitleText("Y-AXIS");
    axisY->setTitleFont(QFont("Inconsolata", 6));
    axisY->setTitleBrush(QBrush(QColor(255, 255, 255)));
    axisY->setLabelsFont(QFont("Inconsolata", 6));
    axisY->setLabelsBrush(QBrush(QColor(255, 255, 255)));

    chart_->addAxis(axisY, Qt::AlignLeft);
    data_->attachAxis(axisY);

    chartView_ = new QChartView(chart_);
    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setVisible(true);
    chartView_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createDummyData();
}

void
ChartWidget::createDummyData()
{
    data_->append(1,1);
    data_->append(2,2);
    data_->append(3,3);
}
