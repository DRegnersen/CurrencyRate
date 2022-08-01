#include "Cache.h"

Cache::Cache(QString filename) : file_(filename) {}

Cache::Cache(Archive source, QString filename)
    : file_(filename), arc_(source) {}

void Cache::set_archive(Archive arc) { arc_ = arc; }

Archive Cache::get_archive() { return arc_; }

void Cache::save() {
    if (!file_.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "<Cache> Writing error";
    }

    QTextStream cache_out(&file_);

    cache_out << arc_.prev_.toString() << "\\";
    cache_out << arc_.capacity_ << "\\";
    cache_out << arc_.size_ << "\\";

    for (int i = 0; i < (int)arc_.size_; i++) {
        cache_out << arc_.rates_[i].get_Date() << "\\";
        cache_out << arc_.rates_[i].get_PreviousDate() << "\\";
        cache_out << arc_.rates_[i].get_PreviousURL().toString() << "\\";
        cache_out << arc_.rates_[i].get_Timestamp() << "\\";
        cache_out << arc_.rates_[i].size() << "\\";

        for (int j = 0; j < (int)arc_.rates_[i].size(); j++) {
            Currency local_cur = arc_.rates_[i].at(j);

            cache_out << local_cur.get_ID() << "\\";
            cache_out << local_cur.get_NumCode() << "\\";
            cache_out << local_cur.get_CharCode() << "\\";
            cache_out << local_cur.get_Nominal() << "\\";
            cache_out << local_cur.get_Name() << "\\";
            cache_out << QString::number(local_cur.get_Value()) << "\\";
            cache_out << local_cur.get_Previous() << "\\";
        }
    }

    file_.close();
}

void Cache::load() {
    if (file_.size() == 0) {
        qDebug() << "<Cache> Cache is empty";
        return;
    }

    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "<Cache> Reading error";
    }

    QTextStream cache_in(&file_);
    QString from_file = cache_in.readAll();
    QStringList data = from_file.split("\\", Qt::SkipEmptyParts);

    arc_.rates_.clear();
    arc_.prev_ = data[0];
    arc_.capacity_ = data[1].toULongLong();
    arc_.size_ = data[2].toULongLong();

    int idx = 3;
    for (int i = 0; i < (int)arc_.size_; i++) {
        QString Date = data[idx++];
        QString PreviousDate = data[idx++];
        QUrl PreviousURL = QUrl(data[idx++]);
        QString Timestamp = data[idx++];
        QVector<Currency> Valute;

        int local_size = data[idx++].toInt();

        for (int j = 0; j < local_size; j++) {
            QVector<QString> cur_info;

            for (int k = 0; k < 7; k++) {
                cur_info.push_back(data[idx++]);
            }

            Valute.push_back(Currency(cur_info));
        }

        arc_.rates_.push_back(
            CurrencyRate(Date, PreviousDate, PreviousURL, Timestamp, Valute));
    }

    file_.close();
}

bool Cache::isEmpty() { return arc_.isEmpty(); }

unsigned long long Cache::size() { return arc_.size(); }
