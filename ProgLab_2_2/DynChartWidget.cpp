#include "DynChartWidget.h"

DynChartWidget::DynChartWidget(const int& idx, Archive& cash) {
    _idx_ = idx;

    if (cash.isEmpty()) {
        _archive_.setSize(PERIOD);
        cash = _archive_;
    } else {
        _archive_ = cash;
    }

    _series_ = new QLineSeries;
    populateSeries();

    _chart_ = new QChart;
    _chart_->addSeries(_series_);
    _chart_->legend()->hide();
    _chart_->setTitle(_archive_[0].at(_idx_).get_CharCode() + " dynamics");

    // X-axis setting
    _axis_x_ = new QDateTimeAxis;
    _axis_x_->setFormat("dd-MMM");
    _axis_x_->setTitleText("All period");
    _chart_->addAxis(_axis_x_, Qt::AlignBottom);
    _series_->attachAxis(_axis_x_);

    // Y-axis setting
    _axis_y_ = new QValueAxis;
    _axis_y_->setLabelFormat("%d");
    _axis_y_->setTitleText(_archive_[0].at(_idx_).get_Name());
    _chart_->addAxis(_axis_y_, Qt::AlignLeft);
    _series_->attachAxis(_axis_y_);

    this->setRenderHint(QPainter::Antialiasing);
    this->setChart(_chart_);
}

void DynChartWidget::populateSeries() {
    QDateTime date;
    for (size_t i = 0; i < _archive_.size(); i++) {
        date = QDateTime::fromString(_archive_[i].get_Date().left(10),
                                     "yyyy-MM-dd");

        _series_->append(date.toMSecsSinceEpoch(),
                         _archive_[i].at(_idx_).get_Value());
    }
}

void DynChartWidget::refresh(int period, Archive& cash) {
    _archive_.setSize(period);
    cash = _archive_;

    _series_->clear();
    _axis_x_->setRange(
        QDateTime::fromString(
            _archive_[_archive_.size() - 1].get_Date().left(10), "yyyy-MM-dd"),
        QDateTime::fromString(_archive_[0].get_Date().left(10), "yyyy-MM-dd"));

    _axis_y_->setRange(std::max(_archive_.min(_idx_) - 3, 0.0),
                       _archive_.max(_idx_) + 3);
    populateSeries();

    this->repaint();
}
