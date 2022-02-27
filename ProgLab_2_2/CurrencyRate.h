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
    QNetworkAccessManager *_manager_;
    QEventLoop _waiting_;
    int _error_code_;

    QString _Date_;
    QString _PreviousDate_;
    QUrl _PreviousURL_;
    QString _Timestamp_;
    QVector<Currency> _Valute_;

    void parseJson(QNetworkReply *reply);

   public:
    CurrencyRate(QObject *parent = nullptr);

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
