#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

#include <map>
#include <memory>

#include "animalswindow.h"
#include "typeswindow.h"
#include "moveswindow.h"
#include "animaldatabase.h"
#include "tdatabase.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_Animals_clicked();

    void on_pushButton_Types_clicked();

    void on_pushButton_Moves_clicked();

private:

    Ui::MainWindow *ui;
    AnimalsWindow * m_animalsWin;
    TypesWindow * m_typesWin;
    MovesWindow * m_movesWin;

    db::Database m_db;

    //std::map<QString, std::shared_ptr<db::TDatabase<Data>>> m_dbs;
    std::map<QString, std::shared_ptr<db::Database>> m_dbMap;

};

#endif // MAINWINDOW_H
