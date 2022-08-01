#include "Currency.h"

Currency::Currency(QVector<QString> data) {
    ID_ = data[0];
    NumCode_ = data[1];
    CharCode_ = data[2];
    Nominal_ = data[3].toInt();
    Name_ = data[4];
    Value_ = data[5].toDouble();
    Previous_ = data[6].toDouble();
}

Currency::Currency(QJsonObject data) {
    ID_ = data.value("ID").toString();
    NumCode_ = data.value("NumCode").toString();
    CharCode_ = data.value("CharCode").toString();
    Nominal_ = data.value("Nominal").toInt();
    Name_ = data.value("Name").toString();
    Value_ = data.value("Value").toDouble();
    Previous_ = data.value("Previous").toDouble();
}

Currency::Currency(const Currency& other) {
    ID_ = other.ID_;
    NumCode_ = other.NumCode_;
    CharCode_ = other.CharCode_;
    Nominal_ = other.Nominal_;
    Name_ = other.Name_;
    Value_ = other.Value_;
    Previous_ = other.Previous_;
}

Currency& Currency::operator=(const Currency& other) {
    ID_ = other.ID_;
    NumCode_ = other.NumCode_;
    CharCode_ = other.CharCode_;
    Nominal_ = other.Nominal_;
    Name_ = other.Name_;
    Value_ = other.Value_;
    Previous_ = other.Previous_;

    return *this;
}

QString Currency::get_ID() const { return ID_; }

QString Currency::get_NumCode() const { return NumCode_; }

QString Currency::get_CharCode() const { return CharCode_; }

int Currency::get_Nominal() const { return Nominal_; }

QString Currency::get_Name() const { return Name_; }

double Currency::get_Value() const { return Value_; }

double Currency::get_Previous() const { return Previous_; }

double Currency::alteration() const { return Value_ - Previous_; }
