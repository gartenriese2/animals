#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    m_animalsWin = new AnimalsWindow(m_db, this);
    m_animalsWin->show();
    this->hide();
}

void MainWindow::on_pushButton_Types_clicked()
{
    m_typesWin = new TypesWindow(m_db, this);
    m_typesWin->show();
    this->hide();
}

void MainWindow::on_pushButton_clicked()
{
    m_movesWin = new MovesWindow(m_db, this);
    m_movesWin->show();
    this->hide();
}
