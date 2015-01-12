#ifndef TYPESWINDOW_H
#define TYPESWINDOW_H

#include <QWidget>
#include <QString>

#include <map>
#include <memory>

#include "datawindow.h"

namespace Ui {
class TypesWindow;
}

class TypesWindow : public QWidget, DataWindow
{
    Q_OBJECT

public:
    explicit TypesWindow(const std::map<QString, std::shared_ptr<db::Database>> &, db::Database &, QWidget *parent = 0);
    ~TypesWindow();

private slots:

    virtual void checkEntry(const QModelIndex &, const QModelIndex &);

    virtual void on_pushButton_Add_clicked();
    virtual void on_pushButton_Insert_clicked();
    virtual void on_pushButton_Delete_clicked();

    virtual void on_pushButton_Save_clicked();
    virtual void on_pushButton_Cancel_clicked();

    virtual void on_lineEdit_Name_editingFinished();

    void on_comboBox_Name_currentTextChanged(const QString &);
    void on_comboBox_Type_currentTextChanged(const QString &);

private:

    Ui::TypesWindow *ui;

    virtual void setCurrent(const QModelIndex &);
    virtual void addNewEntry(const QString &, unsigned int);
    void setEmpty();
    void recalculate();

};

#endif // TYPESWINDOW_H
