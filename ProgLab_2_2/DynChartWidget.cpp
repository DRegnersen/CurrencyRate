#include "DynChartWidget.h"

DynChartWidget::DynChartWidget(const int& idx, Archive& cash) {
    if (cash.isEmpty()) {
        _archive_.setSize(PERIOD);
        cash = _archive_;
    } else {
        _archive_ = cash;
    }
    _chart_ = new QChart;

    // X-axis setting
    _axis_x_ = new QDateTimeAxis;
    _axis_x_->setFormat("dd-MMM");
    _axis_x_->setTitleText("All period");

    // Y-axis setting
    _axis_y_ = new QValueAxis;
    _axis_y_->setLabelFormat("%i");
    _axis_y_->setTitleText(_archive_[0].at(idx).get_Name());

    _chart_->addAxis(_axis_x_, Qt::AlignBottom);
    _chart_->addAxis(_axis_y_, Qt::AlignLeft);

    _series_ = new QLineSeries;

    int year, month, day;
    for (size_t i = 0; i < _archive_.size(); i++) {
        year = _archive_[i].get_Date().section('-', 0, 0).toInt();
        month = _archive_[i].get_Date().section('-', 1, 1).toInt();
        day = _archive_[i].get_Date().section('-', 2, 2).left(2).toInt();

        QDateTime date;
        date.setDate(QDate(year, month, day));

        _series_->append(date.toMSecsSinceEpoch(),
                         _archive_[i].at(idx).get_Value());
    }

    _chart_->addSeries(_series_);
    _chart_->setTitle(_archive_[0].at(idx).get_CharCode() + " dynamics");
    this->setChart(_chart_);
}
