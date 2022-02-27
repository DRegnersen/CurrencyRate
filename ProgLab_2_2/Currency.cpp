#include "Currency.h"

Currency::Currency(QJsonObject data) {
    _ID_ = data.value("ID").toString();
    _NumCode_ = data.value("NumCode").toString();
    _CharCode_ = data.value("CharCode").toString();
    _Nominal_ = data.value("Nominal").toInt();
    _Name_ = data.value("Name").toString();
    _Value_ = data.value("Value").toDouble();
    _Previous_ = data.value("Previous").toDouble();
}

Currency::Currency(const Currency& other) {
    _ID_ = other._ID_;
    _NumCode_ = other._NumCode_;
    _CharCode_ = other._CharCode_;
    _Nominal_ = other._Nominal_;
    _Name_ = other._Name_;
    _Value_ = other._Value_;
    _Previous_ = other._Previous_;
}

Currency& Currency::operator=(const Currency& other) {
    _ID_ = other._ID_;
    _NumCode_ = other._NumCode_;
    _CharCode_ = other._CharCode_;
    _Nominal_ = other._Nominal_;
    _Name_ = other._Name_;
    _Value_ = other._Value_;
    _Previous_ = other._Previous_;

    return *this;
}

QString Currency::get_ID() const { return _ID_; }

QString Currency::get_NumCode() const { return _NumCode_; }

QString Currency::get_CharCode() const { return _CharCode_; }

int Currency::get_Nominal() const { return _Nominal_; }

QString Currency::get_Name() const { return _Name_; }

double Currency::get_Value() const { return _Value_; }

double Currency::get_Previous() const { return _Previous_; }

double Currency::alteration() const { return _Value_ - _Previous_; }
