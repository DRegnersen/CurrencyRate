#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QUrl>
#include <QVector>

#include "CurrencyRate.h"

const QUrl MAINURL = QUrl("https://www.cbr-xml-daily.ru/daily_json.js");
const int LOAD_INTERVAL = 200;

const unsigned int LOWER_PERIOD = 7;
const unsigned int UPPER_PERIOD = 365;
const unsigned int INITIAL_PERIOD = 30;

class Cache;

class Archive {
   private:
    QTimer timer_;

    void add(const unsigned long long& number);

    QVector<CurrencyRate> rates_;
    QUrl prev_;
    unsigned long long size_;
    unsigned long long capacity_;

   public:
    Archive(const Archive& other);

    Archive(QUrl url = MAINURL, unsigned long long size = 0);

    Archive& operator=(const Archive& other);

    CurrencyRate& operator[](const unsigned long long& idx);

    unsigned long long size() const;

    void setSize(unsigned long long size);

    double min(const int& idx);

    double max(const int& idx);

    bool isEmpty();

    QString freshness();

    void refresh();

    friend Cache;
};

#endif  // ARCHIVE_H
