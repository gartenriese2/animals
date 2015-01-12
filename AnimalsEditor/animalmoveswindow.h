#ifndef ANIMALMOVESWINDOW_H
#define ANIMALMOVESWINDOW_H

#include <QWidget>
#include <QString>

#include <vector>
#include <utility>
#include <map>
#include <memory>

#include "numericmodel.h"
#include "animal.h"

#include "database.h"

namespace Ui {
class AnimalMovesWindow;
}

class AnimalMovesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnimalMovesWindow(const std::map<QString, std::shared_ptr<db::Database>> &, db::Database &, const Animal &, QWidget *parent = 0);
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

    db::Database & m_db;
    std::map<QString, std::shared_ptr<db::Database>> m_dbMap;
    Animal m_animal;

};

#endif // ANIMALMOVESWINDOW_H
