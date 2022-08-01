#include "CurrencyTableModel.h"

CurrencyTableModel::CurrencyTableModel(QObject *parent)
    : QAbstractListModel(parent) {}

int CurrencyTableModel::rowCount(const QModelIndex &) const {
    return rate_.size();
}

int CurrencyTableModel::columnCount(const QModelIndex &) const { return 7; }

QVariant CurrencyTableModel::data(const QModelIndex &idx, int role) const {
    QVariant value;

    switch (role) {
        case Qt::DisplayRole: {
            switch (idx.column()) {
                case 0: {
                    value = this->rate_.at(idx.row()).get_NumCode();
                    break;
                }
                case 1: {
                    value = this->rate_.at(idx.row()).get_CharCode();
                    break;
                }
                case 2: {
                    value = this->rate_.at(idx.row()).get_Nominal();
                    break;
                }
                case 3: {
                    value = this->rate_.at(idx.row()).get_Name();
                    break;
                }
                case 4: {
                    value = this->rate_.at(idx.row()).get_Value();
                    break;
                }
                case 5: {
                    if (this->rate_.at(idx.row()).alteration() > 0) {
                        value =
                            "+" + QString::number(
                                      this->rate_.at(idx.row()).alteration());
                    } else {
                        value = this->rate_.at(idx.row()).alteration();
                    }
                    break;
                }
                case 6: {
                    value = "Show...";
                    break;
                }
            }
        } break;
        case Qt::UserRole: {
            value = this->rate_.at(idx.row()).get_CharCode();
        } break;

        default:
            break;
    }

    return value;
}

QVariant CurrencyTableModel::headerData(int column, Qt::Orientation orientation,
                                        int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (column) {
            case 0:
                return "Num. Code";
            case 1:
                return "Char. Code";
            case 2:
                return "Nominal";
            case 3:
                return "Currency";
            case 4:
                return "Rate";
            case 5:
                return "Alteration";
            case 6:
                return "Dynamics";
        }
    }
    return QVariant();
}

void CurrencyTableModel::populate(CurrencyRate new_rate) {
    int idx = this->rate_.size();
    this->beginInsertRows(QModelIndex(), 1, idx);
    this->rate_ = new_rate;

    endInsertRows();
}
