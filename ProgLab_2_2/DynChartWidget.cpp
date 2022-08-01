#include "DynChartWidget.h"

DynChartWidget::DynChartWidget(const int& idx, Cache& cache) {
    idx_ = idx;

    cache.load();

    if (cache.isEmpty()) {
        archive_.setSize(INITIAL_PERIOD);
        cache.set_archive(archive_);
        cache.save();
    } else {
        archive_ = cache.get_archive();
        archive_.refresh();
    }

    series_ = new QLineSeries;
    populateSeries();

    chart_ = new QChart;
    chart_->addSeries(series_);
    chart_->legend()->hide();
    chart_->setTitle(archive_[0].at(idx_).get_CharCode() + " dynamics");

    // X-axis setting
    axis_x_ = new QDateTimeAxis;
    axis_x_->setFormat("dd-MMM");
    axis_x_->setTitleText("All period");
    chart_->addAxis(axis_x_, Qt::AlignBottom);
    series_->attachAxis(axis_x_);

    // Y-axis setting
    axis_y_ = new QValueAxis;
    axis_y_->setLabelFormat("%d");
    axis_y_->setTitleText(archive_[0].at(idx_).get_Name());
    chart_->addAxis(axis_y_, Qt::AlignLeft);
    series_->attachAxis(axis_y_);

    this->setRenderHint(QPainter::Antialiasing);
    this->setChart(chart_);
}

void DynChartWidget::populateSeries() {
    QDateTime date;
    for (size_t i = 0; i < archive_.size(); i++) {
        date = QDateTime::fromString(archive_[i].get_Date().left(10),
                                     "yyyy-MM-dd");

        series_->append(date.toMSecsSinceEpoch(),
                        archive_[i].at(idx_).get_Value());
    }
}

void DynChartWidget::refresh(int period, Cache& cache) {
    archive_.setSize(period);
    cache.set_archive(archive_);
    cache.save();

    series_->clear();
    axis_x_->setRange(
        QDateTime::fromString(archive_[archive_.size() - 1].get_Date().left(10),
                              "yyyy-MM-dd"),
        QDateTime::fromString(archive_[0].get_Date().left(10), "yyyy-MM-dd"));

    axis_y_->setRange(std::max(archive_.min(idx_) - 3, 0.0),
                      archive_.max(idx_) + 3);
    populateSeries();

    this->repaint();
}
