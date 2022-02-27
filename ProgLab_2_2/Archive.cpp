#include "Archive.h"

void Archive::add(const unsigned long long& number) {
    _capacity_ += number;
    _size_ = _capacity_;

    for (size_t i = 0; i < number; i++) {
        CurrencyRate rate(_prev_);
        rate.validateRate();

        _rates_.push_back(rate);

        _prev_ = rate.get_PreviousURL();

        _timer_.start(500);
        _timer_.stop();
    }
}

Archive::Archive(QUrl url, unsigned long long size) {
    _capacity_ = 0;
    _prev_ = url;

    add(size);
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
    if (size <= _size_) {
        _size_ = size;
        return;
    }

    add(size - _size_);
}

bool Archive::isEmpty() { return _size_ == 0; }