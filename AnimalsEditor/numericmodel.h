#ifndef NUMERICMODEL_H
#define NUMERICMODEL_H

#include <QStandardItemModel>
#include <QDebug>

class NumericModel : public QStandardItemModel
{
public:

    enum Role {
        SortRole=Qt::UserRole
    };

    NumericModel() {}
    ~NumericModel() {}

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const {

        if (role == SortRole) {
            return index.data().toUInt();
        }

        return QStandardItemModel::data(index, role);

    }

};

#endif // NUMERICMODEL_H
