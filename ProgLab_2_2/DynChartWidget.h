#ifndef DYNCHARTWIDGET_H
#define DYNCHARTWIDGET_H

#define PERIOD 14

#include <QChartView>
#include <QDate>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QValueAxis>

#include "Archive.h"
#include "CurrencyRate.h"

class DynChartWidget : public QChartView {
   private:
    Archive _archive_;
    QChart* _chart_;
    QLineSeries* _series_;
    QDateTimeAxis* _axis_x_;
    QValueAxis* _axis_y_;

   public:
    DynChartWidget(const int& idx);
};

#endif  // DYNCHARTWIDGET_H
