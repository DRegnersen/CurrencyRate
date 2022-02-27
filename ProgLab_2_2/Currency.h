#ifndef CURRENCY_H
#define CURRENCY_H

#include <QJsonObject>
#include <QString>

class Currency {
   private:
    QString _ID_;
    QString _NumCode_;
    QString _CharCode_;
    int _Nominal_;
    QString _Name_;
    double _Value_;
    double _Previous_;

   public:
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
