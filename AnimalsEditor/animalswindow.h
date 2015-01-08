#ifndef ANIMALSWINDOW_H
#define ANIMALSWINDOW_H

#include <QWidget>

#include "datawindow.h"
#include "animalmoveswindow.h"

namespace Ui {
class AnimalsWindow;
}

class AnimalsWindow : public QWidget, DataWindow
{
    Q_OBJECT

public:
    explicit AnimalsWindow(Database &, QWidget *parent = 0);
    ~AnimalsWindow();

private slots:

    void checkEntry(const QModelIndex &, const QModelIndex &);

    virtual void on_pushButton_Add_clicked();
    virtual void on_pushButton_Insert_clicked();
    virtual void on_pushButton_Delete_clicked();

    virtual void on_pushButton_Save_clicked();
    virtual void on_pushButton_Cancel_clicked();

    virtual void on_lineEdit_Name_editingFinished();

    void on_lineEdit_HP_textChanged(const QString &arg1);
    void on_lineEdit_Attack_textChanged(const QString &arg1);
    void on_lineEdit_Defense_textChanged(const QString &arg1);
    void on_lineEdit_Speed_textChanged(const QString &arg1);
    void on_lineEdit_SpecialAttack_textChanged(const QString &arg1);
    void on_lineEdit_SpecialDefense_textChanged(const QString &arg1);
    void on_lineEdit_BaseXP_textChanged(const QString &arg1);

    void on_comboBox_Secondary_currentTextChanged(const QString &arg1);
    void on_comboBox_Primary_currentTextChanged(const QString &arg1);

    void on_pushButton_EditMoves_clicked();

private:

    Ui::AnimalsWindow *ui;

    AnimalMovesWindow * m_editMovesWin;

    virtual void setCurrent(const QModelIndex &);
    virtual void addNewEntry(const QString &name, unsigned int);
    void setEmpty();
    void init();

};

#endif // ANIMALSWINDOW_H
