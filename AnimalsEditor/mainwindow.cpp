#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db::TDatabase<Move> db;
    m_dbMap.emplace("Animals", std::make_shared<db::AnimalDatabase>());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Animals_clicked()
{
    m_animalsWin = new AnimalsWindow(m_dbMap, m_db, this);
    m_animalsWin->show();
    this->hide();
}

void MainWindow::on_pushButton_Types_clicked()
{
    m_typesWin = new TypesWindow(m_dbMap, m_db, this);
    m_typesWin->show();
    this->hide();
}

void MainWindow::on_pushButton_Moves_clicked()
{
    m_movesWin = new MovesWindow(m_dbMap, m_db, this);
    m_movesWin->show();
    this->hide();
}
