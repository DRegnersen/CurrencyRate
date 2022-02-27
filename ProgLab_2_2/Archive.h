#ifndef ARCHIVE_H
#define ARCHIVE_H

#define MAINURL QUrl("https://www.cbr-xml-daily.ru/daily_json.js")

#include <QTimer>
#include <QUrl>
#include <QVector>

#include "CurrencyRate.h"

class Archive {
   private:
    QVector<CurrencyRate> _rates_;
    QUrl _prev_;
    unsigned long long _size_;
    unsigned long long _capacity_;
    QTimer _timer_;

    void add(const unsigned long long& number);

   public:
    Archive(QUrl url = MAINURL, unsigned long long size = 0);

    CurrencyRate& operator[](const unsigned long long& idx);

    unsigned long long size() const;

    void setSize(unsigned long long size);

    bool isEmpty();
};

#endif  // ARCHIVE_H
