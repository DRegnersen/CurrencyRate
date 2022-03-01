#include "Archive.h"

void Archive::add(const unsigned long long& number) {
    bool downloaded = false;
    _capacity_ += number;
    _size_ = _capacity_;

    for (size_t i = 0; i < number; i++) {
        if (i == 0) {
            qDebug() << "<Archive> Downloading has started. Do not run other "
                        "processes";
        }

        if (!_prev_.toString().contains("https:")) {
            _prev_ = QUrl("https:" + _prev_.toString());
        }

        CurrencyRate rate(_prev_);
        rate.validateRate();

        _rates_.push_back(rate);
        qDebug() << "<Archive> Downloading: "
                 << (int)(((double)(i + 1) / (double)number) * 100) << "%";

        _prev_ = rate.get_PreviousURL();

        if (i != number - 1) {
            _timer_.start(INTERVAL);
            _timer_.stop();
        } else {
            downloaded = true;
        }
    }
    if (downloaded) {
        qDebug()
            << "<Archive> Actual currency rate has been succesfully downloaded";
    }
}

Archive::Archive(QUrl url, unsigned long long size) {
    _capacity_ = 0;
    _prev_ = url;

    add(size);
}

Archive& Archive::operator=(const Archive& other) {
    _rates_.clear();
    _prev_ = other._prev_;
    _size_ = other._size_;
    _capacity_ = other._capacity_;

    for (const CurrencyRate& rate : other._rates_) {
        _rates_.push_back(rate);
    }

    return *this;
}

CurrencyRate& Archive::operator[](const unsigned long long& idx) {
    if (idx >= _size_) {
        qDebug() << "<Archive> Index is out of range";
        static CurrencyRate error_rate;
        return error_rate;
    }
    return _rates_[idx];
}

unsigned long long Archive::size() const { return _size_; }

void Archive::setSize(unsigned long long size) {
    if (size <= _capacity_) {
        _size_ = size;
        return;
    }

    add(size - _size_);
}

bool Archive::isEmpty() { return _size_ == 0; }

double Archive::min(const int& idx) {
    double min = -1;

    for (size_t i = 0; i < _size_; i++) {
        if (min < 0) {
            min = _rates_[i].at(idx).get_Value();
        } else {
            min = std::min(min, _rates_[i].at(idx).get_Value());
        }
    }

    return min;
}

double Archive::max(const int& idx) {
    double max = -1;

    for (size_t i = 0; i < _size_; i++) {
        if (max < 0) {
            max = _rates_[i].at(idx).get_Value();
        } else {
            max = std::max(max, _rates_[i].at(idx).get_Value());
        }
    }

    return max;
}

double max(const int& idx);
