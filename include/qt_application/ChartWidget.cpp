#include "ChartWidget.h"

ChartWidget::ChartWidget()
{
    chart_     = new QChart();
    chartView_ = new QChartView(chart_);
    axisX_     = new QValueAxis;
    axisY_     = new QValueAxis;

    chart_->legend()->hide();
    chart_->setVisible(true);
    chart_->setTitle("TITLE");
    chart_->setTitleFont(QFont("Roboto Mono", 8, QFont::Bold));
    chart_->setTitleBrush(QBrush(QColor(255, 255, 255)));
    chart_->setBackgroundBrush(QBrush(QColor(60, 60, 60)));
    chart_->setMargins(QMargins(0,0,0,0)); 

    // Custom X axis
    axisX_->setRange(0, 4);
    axisX_->setTickCount(9); // Matches your range and grid style
    axisX_->setTitleText("X-AXIS");
    axisX_->setTitleFont(QFont("Inconsolata", 6));
    axisX_->setTitleBrush(QBrush(QColor(255, 255, 255)));
    axisX_->setLabelsFont(QFont("Inconsolata", 6));
    axisX_->setLabelsBrush(QBrush(QColor(255, 255, 255)));

    chart_->addAxis(axisX_, Qt::AlignBottom);

    // Custom Y axis
    axisY_->setRange(0, 4);
    axisY_->setTickCount(9);
    axisY_->setTitleText("Y-AXIS");
    axisY_->setTitleFont(QFont("Inconsolata", 6));
    axisY_->setTitleBrush(QBrush(QColor(255, 255, 255)));
    axisY_->setLabelsFont(QFont("Inconsolata", 6));
    axisY_->setLabelsBrush(QBrush(QColor(255, 255, 255)));

    chart_->addAxis(axisY_, Qt::AlignLeft);

    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setVisible(true);
    chartView_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    addLineSeries();
    createDummyData();
}


void 
ChartWidget::addLineSeries(int r, int g, int b)
{
    data_.insert(data_.end(), new QLineSeries());
    chart_->addSeries(data_.back());
    data_.back()->attachAxis(axisX_);
    data_.back()->attachAxis(axisY_);
    data_.back()->setPen(QPen(QColor(r, g, b), 1)); // Thin line
}


void ChartWidget::createDummyData()
{
    data_.back()->append(1,1);
    data_.back()->append(2,2);
    data_.back()->append(3,3);
}
