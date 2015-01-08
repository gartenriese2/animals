#include "comboboxdelegate.h"

#include <QComboBox>
#include <QApplication>
#include <QDebug>

ComboBoxDelegate::ComboBoxDelegate(QObject * parent)
  : QItemDelegate(parent)
{

}

ComboBoxDelegate::~ComboBoxDelegate()
{

}

void ComboBoxDelegate::setItems(const std::vector<QString> & items) {
    m_items = items;
}

QWidget * ComboBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QComboBox * editor = new QComboBox(parent);
    for (const auto & item : m_items) {
        editor->addItem(item);
    }
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
    QComboBox * comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentText(index.data().toString());
}

void ComboBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    QComboBox * comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText());
}

void ComboBoxDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QStyleOptionViewItemV4 myOption = option;
    myOption.text = index.data().toString();
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
