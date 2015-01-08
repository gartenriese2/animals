#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "animalswindow.h"
#include "typeswindow.h"
#include "moveswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_Types_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    AnimalsWindow * m_animalsWin;
    TypesWindow * m_typesWin;
    MovesWindow * m_movesWin;

    Database m_db;
};

#endif // MAINWINDOW_H
