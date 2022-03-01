#ifndef ARCHIVE_H
#define ARCHIVE_H

#define MAINURL QUrl("https://www.cbr-xml-daily.ru/daily_json.js")
#define INTERVAL 200

#include <QTimer>
#include <QUrl>
#include <QVector>

#include "CurrencyRate.h"

class Archive {
   private:
    QTimer _timer_;

    QVector<CurrencyRate> _rates_;

    QUrl _prev_;
    unsigned long long _size_;
    unsigned long long _capacity_;

    void add(const unsigned long long& number);

   public:
    Archive(QUrl url = MAINURL, unsigned long long size = 0);

    Archive& operator=(const Archive& other);

    CurrencyRate& operator[](const unsigned long long& idx);

    unsigned long long size() const;

    void setSize(unsigned long long size);

    double min(const int& idx);

    double max(const int& idx);

    bool isEmpty();
};

#endif  // ARCHIVE_H
