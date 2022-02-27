#ifndef CURRENCYTABLEMODEL_H
#define CURRENCYTABLEMODEL_H

#include <Currency.h>
#include <CurrencyRate.h>

#include <QList>
#include <QModelIndex>
#include <QPushButton>
#include <QVariant>
#include <QVector>

class CurrencyTableModel : public QAbstractListModel {
   private:
    CurrencyRate _rate_;

   public:
    CurrencyTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &) const;

    int columnCount(const QModelIndex &) const;

    QVariant data(const QModelIndex &idx, int role) const;

    QVariant headerData(int column, Qt::Orientation orientation,
                        int role) const;

    void populate(CurrencyRate new_rate);
};

#endif  // CURRENCYTABLEMODEL_H
