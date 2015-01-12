#ifndef MOVESWINDOW_H
#define MOVESWINDOW_H

#include <QWidget>
#include <QString>

#include <map>
#include <memory>

#include "datawindow.h"

namespace Ui {
class MovesWindow;
}

class MovesWindow : public QWidget, DataWindow
{
    Q_OBJECT

public:
    explicit MovesWindow(const std::map<QString, std::shared_ptr<db::Database>> &, db::Database &, QWidget *parent = 0);
    ~MovesWindow();

private slots:

    void checkEntry(const QModelIndex &, const QModelIndex &);

    virtual void on_pushButton_Add_clicked();
    virtual void on_pushButton_Insert_clicked();
    virtual void on_pushButton_Delete_clicked();

    virtual void on_pushButton_Save_clicked();
    virtual void on_pushButton_Cancel_clicked();

    virtual void on_lineEdit_Name_editingFinished();

    void on_lineEdit_BaseDamage_textChanged(const QString &);
    void on_lineEdit_Accuracy_textChanged(const QString &);
    void on_lineEdit_Priority_textChanged(const QString &);

    void on_comboBox_Type_currentTextChanged(const QString &);
    void on_comboBox_Category_currentTextChanged(const QString &);

private:

    Ui::MovesWindow *ui;

    virtual void setCurrent(const QModelIndex &current);
    virtual void addNewEntry(const QString &name, unsigned int);
    void setEmpty();

};

#endif // MOVESWINDOW_H
