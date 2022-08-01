#ifndef DYNCHARTWIDGET_H
#define DYNCHARTWIDGET_H

#include <QChart>
#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QString>
#include <QValueAxis>

#include "Archive.h"
#include "Cache.h"
#include "CurrencyRate.h"

class DynChartWidget : public QChartView {
   private:
    int idx_;

    Archive archive_;
    QChart* chart_;
    QLineSeries* series_;
    QDateTimeAxis* axis_x_;
    QValueAxis* axis_y_;

    void populateSeries();

   public:
    DynChartWidget(const int& idx, Cache& cache);

    void refresh(int period, Cache& cache);
};

#endif  // DYNCHARTWIDGET_H
