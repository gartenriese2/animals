#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>

#include <vector>

class ComboBoxDelegate : public QItemDelegate {

    Q_OBJECT

public:

    ComboBoxDelegate(QObject * = 0);
    ~ComboBoxDelegate();

    QWidget * createEditor(QWidget *, const QStyleOptionViewItem &,
                           const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setItems(const std::vector<QString> &);

private:

    std::vector<QString> m_items;

};

#endif // COMBOBOXDELEGATE_H
