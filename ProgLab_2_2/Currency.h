#ifndef CURRENCY_H
#define CURRENCY_H

#include <QJsonObject>
#include <QString>

class Currency {
   private:
    QString ID_;
    QString NumCode_;
    QString CharCode_;
    int Nominal_;
    QString Name_;
    double Value_;
    double Previous_;

   public:
    Currency(QVector<QString> data);

    Currency(QJsonObject data);

    Currency(const Currency& other);

    Currency& operator=(const Currency& other);

    QString get_ID() const;

    QString get_NumCode() const;

    QString get_CharCode() const;

    int get_Nominal() const;

    QString get_Name() const;

    double get_Value() const;

    double get_Previous() const;

    double alteration() const;
};

#endif  // CURRENCY_H
