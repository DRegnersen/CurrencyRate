#ifndef CURRENCYRATE_H
#define CURRENCYRATE_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrl>
#include <QVector>

#include "Currency.h"

class CurrencyRate : public QObject {
   private:
    QNetworkAccessManager *manager_;
    QEventLoop waiting_;
    int error_code_;

    QString Date_;
    QString PreviousDate_;
    QUrl PreviousURL_;
    QString Timestamp_;
    QVector<Currency> Valute_;

   private slots:
    void parseJson(QNetworkReply *reply);

   public:
    CurrencyRate(QObject *parent = nullptr);

    CurrencyRate(QString Date, QString PreviousDate, QUrl PreviousURL,
                 QString Timestamp, QVector<Currency> Valute,
                 QObject *parent = nullptr);

    CurrencyRate(const CurrencyRate &other, QObject *parent = nullptr);

    CurrencyRate(QUrl url, QObject *parent = nullptr);

    CurrencyRate &operator=(const CurrencyRate &other);

    void validateRate();

    unsigned int size() const;

    Currency at(const unsigned int &idx) const;

    QString get_Date() const;

    QString get_PreviousDate() const;

    QUrl get_PreviousURL() const;

    QString get_Timestamp() const;

    int error() const;
};

#endif  // CURRENCYRATE_H
