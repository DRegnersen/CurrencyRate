#ifndef DYNCHARTWIDGET_H
#define DYNCHARTWIDGET_H

#define PERIOD 30

#include <QChart>
#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QString>
#include <QValueAxis>

#include "Archive.h"
#include "CurrencyRate.h"

class DynChartWidget : public QChartView {
   private:
    int _idx_;

    Archive _archive_;
    QChart* _chart_;
    QLineSeries* _series_;
    QDateTimeAxis* _axis_x_;
    QValueAxis* _axis_y_;

    void populateSeries();

   public:
    DynChartWidget(const int& idx, Archive& cash);

    void refresh(int period, Archive& cash);
};

#endif  // DYNCHARTWIDGET_H
