#ifndef ANIMALMOVESWINDOW_H
#define ANIMALMOVESWINDOW_H

#include <QWidget>
#include <QString>

#include <vector>
#include <utility>

#include "numericmodel.h"
#include "animal.h"

class Database;

namespace Ui {
class AnimalMovesWindow;
}

class AnimalMovesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnimalMovesWindow(Database &, const Animal &, QWidget *parent = 0);
    ~AnimalMovesWindow();

private slots:

    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();

    void on_pushButton_AddMove_clicked();
    void on_pushButton_DeleteMove_clicked();

private:

    Ui::AnimalMovesWindow *ui;
    QWidget * m_parent;

    NumericModel m_movesModel;

    Database & m_db;
    Animal m_animal;

};

#endif // ANIMALMOVESWINDOW_H
