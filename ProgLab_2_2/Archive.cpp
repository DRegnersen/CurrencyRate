#include "Archive.h"

Archive::Archive(const Archive& other) {
    prev_ = other.prev_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    rates_ = other.rates_;
}

Archive::Archive(QUrl url, unsigned long long size) {
    capacity_ = 0;
    prev_ = url;
    add(size);
}

void Archive::add(const unsigned long long& number) {
    bool downloaded = false;
    capacity_ += number;
    size_ = capacity_;

    for (size_t i = 0; i < number; i++) {
        if (i == 0) {
            qDebug() << "<Archive> Downloading has started. Do not run other "
                        "processes";
        }

        if (!prev_.toString().contains("https:")) {
            prev_ = QUrl("https:" + prev_.toString());
        }

        CurrencyRate rate(prev_);
        rate.validateRate();

        rates_.push_back(rate);
        qDebug() << "<Archive> Downloading: "
                 << (int)(((double)(i + 1) / (double)number) * 100) << "%";

        prev_ = rate.get_PreviousURL();

        if (i != number - 1) {
            timer_.start(LOAD_INTERVAL);
            timer_.stop();
        } else {
            downloaded = true;
        }
    }
    if (downloaded) {
        qDebug()
            << "<Archive> Actual currency rate has been succesfully downloaded";
    }
}

Archive& Archive::operator=(const Archive& other) {
    prev_ = other.prev_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    rates_ = other.rates_;

    return *this;
}

CurrencyRate& Archive::operator[](const unsigned long long& idx) {
    if (idx >= size_) {
        qDebug() << "<Archive> Index is out of range";
        static CurrencyRate error_rate;
        return error_rate;
    }
    return rates_[idx];
}

unsigned long long Archive::size() const { return size_; }

void Archive::setSize(unsigned long long size) {
    if (size <= capacity_) {
        size_ = size;
        return;
    }

    add(size - size_);
}

bool Archive::isEmpty() { return size_ == 0; }

double Archive::min(const int& idx) {
    double min = -1;

    for (size_t i = 0; i < size_; i++) {
        if (min < 0) {
            min = rates_[i].at(idx).get_Value();
        } else {
            min = std::min(min, rates_[i].at(idx).get_Value());
        }
    }

    return min;
}

double Archive::max(const int& idx) {
    double max = -1;

    for (size_t i = 0; i < size_; i++) {
        if (max < 0) {
            max = rates_[i].at(idx).get_Value();
        } else {
            max = std::max(max, rates_[i].at(idx).get_Value());
        }
    }

    return max;
}

QString Archive::freshness() { return rates_[0].get_Date(); }

void Archive::refresh() {
    QUrl actual_url = MAINURL;
    QVector<CurrencyRate> fresh_rates;

    qDebug() << "<Archive> Updating...";

    while (true) {
        if (!actual_url.toString().contains("https:")) {
            actual_url = QUrl("https:" + prev_.toString());
        }

        CurrencyRate rate(actual_url);
        rate.validateRate();

        QDateTime start_date =
            QDateTime::fromString(freshness().left(10), "yyyy-MM-dd");
        QDateTime end_date =
            QDateTime::fromString(rate.get_Date().left(10), "yyyy-MM-dd");

        if (start_date.daysTo(end_date) <= 0) {
            break;
        }

        fresh_rates.push_back(rate);
        timer_.start(LOAD_INTERVAL);
        timer_.stop();
    }

    for (int i = 0; i < fresh_rates.size(); i++) {
        rates_.pop_back();
    }
    rates_ = fresh_rates + rates_;
    prev_ = rates_[size_ - 1].get_PreviousURL();
}
