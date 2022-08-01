#include "CurrencyRate.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

CurrencyRate::CurrencyRate(QObject *parent) : QObject(parent) {}

CurrencyRate::CurrencyRate(QString Date, QString PreviousDate, QUrl PreviousURL,
                           QString Timestamp, QVector<Currency> Valute,
                           QObject *parent)
    : QObject(parent) {
    Date_ = Date;
    PreviousDate_ = PreviousDate;
    PreviousURL_ = PreviousURL;
    Timestamp_ = Timestamp;
    Valute_ = Valute;
}

CurrencyRate::CurrencyRate(const CurrencyRate &other, QObject *parent)
    : QObject(parent) {
    Date_ = other.Date_;
    PreviousDate_ = other.PreviousDate_;
    PreviousURL_ = other.PreviousURL_;
    Timestamp_ = other.Timestamp_;
    Valute_ = other.Valute_;
}

CurrencyRate::CurrencyRate(QUrl url, QObject *parent) : QObject(parent) {
    manager_ = new QNetworkAccessManager;

    connect(manager_, &QNetworkAccessManager::finished, this,
            &CurrencyRate::parseJson);

    connect(manager_, &QNetworkAccessManager::finished, &waiting_,
            &QEventLoop::quit);

    manager_->get(QNetworkRequest(url));
}

void CurrencyRate::parseJson(QNetworkReply *reply) {
    if (!(error_code_ = reply->error())) {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();
        QJsonObject js_valute = root.value(root.keys().at(4)).toObject();

        Date_ = root.value(root.keys().at(0)).toString();
        PreviousDate_ = root.value(root.keys().at(1)).toString();
        PreviousURL_ = root.value(root.keys().at(2)).toString();
        Timestamp_ = root.value(root.keys().at(3)).toString();

        QJsonObject js_current;
        for (int i = 0; i < js_valute.size(); i++) {
            js_current = js_valute.value(js_valute.keys().at(i)).toObject();
            Valute_.push_back(Currency(js_current));
        }
    } else {
        qDebug() << "<CurrencyRate> Reply was not transmitted";
    }
    reply->deleteLater();
}

CurrencyRate &CurrencyRate::operator=(const CurrencyRate &other) {
    Date_ = other.Date_;
    PreviousDate_ = other.PreviousDate_;
    PreviousURL_ = other.PreviousURL_;
    Timestamp_ = other.Timestamp_;
    Valute_ = other.Valute_;

    return *this;
}

void CurrencyRate::validateRate() { waiting_.exec(); }

unsigned int CurrencyRate::size() const { return Valute_.size(); }

Currency CurrencyRate::at(const unsigned int &idx) const {
    return Valute_[idx];
}

QString CurrencyRate::get_Date() const { return Date_; }

QString CurrencyRate::get_PreviousDate() const { return PreviousDate_; }

QUrl CurrencyRate::get_PreviousURL() const { return PreviousURL_; }

QString CurrencyRate::get_Timestamp() const { return Timestamp_; }

int CurrencyRate::error() const { return error_code_; }
