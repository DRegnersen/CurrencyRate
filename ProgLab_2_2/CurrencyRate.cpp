#include "CurrencyRate.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

CurrencyRate::CurrencyRate(QObject *parent) : QObject(parent) {}

CurrencyRate::CurrencyRate(const CurrencyRate &other, QObject *parent)
    : QObject(parent) {
    _Date_ = other._Date_;
    _PreviousDate_ = other._PreviousDate_;
    _PreviousURL_ = other._PreviousURL_;
    _Timestamp_ = other._Timestamp_;
    _Valute_.clear();

    for (const Currency &currency : other._Valute_) {
        _Valute_.push_back(currency);
    }
}

CurrencyRate::CurrencyRate(QUrl url, QObject *parent) : QObject(parent) {
    _manager_ = new QNetworkAccessManager;

    connect(_manager_, &QNetworkAccessManager::finished, this,
            &CurrencyRate::parseJson);

    connect(_manager_, &QNetworkAccessManager::finished, &_waiting_,
            &QEventLoop::quit);

    _manager_->get(QNetworkRequest(url));
}

void CurrencyRate::parseJson(QNetworkReply *reply) {
    int error_code;
    if (!(error_code = reply->error())) {
        qDebug() << reply->url();
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();
        QJsonObject js_valute = root.value(root.keys().at(4)).toObject();

        _Date_ = root.value(root.keys().at(0)).toString();
        _PreviousDate_ = root.value(root.keys().at(1)).toString();
        _PreviousURL_ = root.value(root.keys().at(2)).toString();
        _Timestamp_ = root.value(root.keys().at(3)).toString();

        QJsonObject js_current;
        for (int i = 0; i < js_valute.size(); i++) {
            js_current = js_valute.value(js_valute.keys().at(i)).toObject();
            _Valute_.push_back(Currency(js_current));
        }
    } else {
        qDebug() << "<CurrencyRate> Reply was not transmitted";
        qDebug() << reply->url();
        qDebug() << error_code;
    }
    reply->deleteLater();
}

CurrencyRate &CurrencyRate::operator=(const CurrencyRate &other) {
    _Date_ = other._Date_;
    _PreviousDate_ = other._PreviousDate_;
    _PreviousURL_ = other._PreviousURL_;
    _Timestamp_ = other._Timestamp_;
    _Valute_.clear();

    for (const Currency &currency : other._Valute_) {
        _Valute_.push_back(currency);
    }

    return *this;
}

void CurrencyRate::validateRate() { _waiting_.exec(); }

unsigned int CurrencyRate::size() const { return _Valute_.size(); }

Currency CurrencyRate::at(const unsigned int &idx) const {
    return _Valute_[idx];
}

QString CurrencyRate::get_Date() const { return _Date_; }

QString CurrencyRate::get_PreviousDate() const { return _PreviousDate_; }

QUrl CurrencyRate::get_PreviousURL() const { return _PreviousURL_; }

QString CurrencyRate::get_Timestamp() const { return _Timestamp_; }
