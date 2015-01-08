#include "moveswindow.h"
#include "ui_moveswindow.h"

#include <QInputDialog>

#include <iostream>
#include <cassert>

constexpr unsigned int k_minBaseDamage {0};
constexpr unsigned int k_maxBaseDamage {250};
constexpr unsigned int k_minAccuracy {0};
constexpr unsigned int k_maxAccuracy {100};
constexpr int k_minPriority {-6};
constexpr int k_maxPriority {6};

MovesWindow::MovesWindow(Database & db, QWidget *parent) :
    QWidget(),
    DataWindow(parent, db),
    ui(new Ui::MovesWindow)
{
    ui->setupUi(this);

    QStringList list;
    const auto map = m_db.getMovesByID();
    for (const auto & entry : map) {

        list << entry.second.getName();

    }
    m_nameList.setStringList(list);

    ui->comboBox_Type->addItem("");
    for (const auto & type : m_db.getTypesByID()) {
        ui->comboBox_Type->addItem(type.second.getName());
    }

    ui->comboBox_Category->addItem("");
    ui->comboBox_Category->addItem("Physical");
    ui->comboBox_Category->addItem("Special");
    ui->comboBox_Category->addItem("Status");

    setEmpty();

    ui->listView->setModel(&m_nameList);
    ui->listView->setCurrentIndex(m_nameList.index(0));
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QValidator * baseDamageValidator = new QIntValidator(k_minBaseDamage, k_maxBaseDamage, this);
    ui->lineEdit_BaseDamage->setValidator(baseDamageValidator);
    QValidator * accuracyVaildator = new QIntValidator(k_minAccuracy, k_maxAccuracy, this);
    ui->lineEdit_Accuracy->setValidator(accuracyVaildator);
    QValidator * priorityValidator = new QIntValidator(k_minPriority, k_maxPriority, this);
    ui->lineEdit_Priority->setValidator(priorityValidator);

    setCurrent(m_nameList.index(0));

    connect(ui->listView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(checkEntry(QModelIndex,QModelIndex)));

}

MovesWindow::~MovesWindow()
{
    delete ui;
}

void MovesWindow::checkEntry(const QModelIndex & current, const QModelIndex & previous) {

    DataWindow::checkEntry(current, previous);

}

void MovesWindow::setCurrent(const QModelIndex & current)
{

    if (!current.isValid()) return;

    const auto name = current.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    const auto move = m_db.getMoves().at(name);

    ui->lineEdit_Name->setText(name);

    ui->comboBox_Type->setCurrentText(move.getType());
    ui->comboBox_Category->setCurrentText(move.getCategory());

    ui->lineEdit_BaseDamage->setText(QString::number(move.getBaseDamage()));
    ui->lineEdit_Accuracy->setText(QString::number(move.getAccuracy()));
    ui->lineEdit_Priority->setText(QString::number(move.getPriority()));

}

void MovesWindow::addNewEntry(const QString & name, unsigned int row)
{

    Move move;
    move.setName(name);
    move.setID(row + 1);

    assert(m_db.insertMove(row + 1, move));

}

void MovesWindow::setEmpty()
{

    ui->lineEdit_Name->setText("");

    ui->comboBox_Type->setCurrentIndex(0);
    ui->comboBox_Category->setCurrentIndex(0);

    ui->lineEdit_BaseDamage->setText("0");
    ui->lineEdit_Accuracy->setText("100");
    ui->lineEdit_Priority->setText("0");

}

void MovesWindow::on_pushButton_Add_clicked()
{

    bool ok;
    const auto text = QInputDialog::getText(this, "Move Editor", "Enter a name:", QLineEdit::Normal,
            QString::null, &ok);
    if (!ok || text.isEmpty()) return;

    const auto row = m_nameList.rowCount();
    m_nameList.insertRows(row, 1);

    const auto idx = m_nameList.index(row);
    ui->listView->setCurrentIndex(idx);
    m_nameList.setData(ui->listView->currentIndex(), text);

    addNewEntry(text, row);
    setCurrent(idx);

}

void MovesWindow::on_pushButton_Insert_clicked()
{
    bool ok;
    const auto text = QInputDialog::getText(this, "Move Editor", "Enter a name:", QLineEdit::Normal,
            QString::null, &ok);
    if (!ok || text.isEmpty()) return;

    auto row = ui->listView->currentIndex().row();
    if (!ui->listView->currentIndex().isValid()) {
        row = m_nameList.rowCount();
    } else {
        ++row;
    }
    m_nameList.insertRows(row, 1);

    const auto idx = m_nameList.index(row);
    ui->listView->setCurrentIndex(idx);
    m_nameList.setData(ui->listView->currentIndex(), text);

    addNewEntry(text, row);
    setCurrent(idx);
}

void MovesWindow::on_pushButton_Delete_clicked()
{
    const auto idx = ui->listView->currentIndex();
    assert(idx.isValid());

    const auto name = idx.data().toString();

    if (idx.row() == 0) {
        // first element to be deleted
        if (m_nameList.rowCount() == 1) {
            // only one remaining element
            setEmpty();
        } else {
            ui->listView->setCurrentIndex(m_nameList.index(1));
        }
    } else {
        ui->listView->setCurrentIndex(m_nameList.index(0));
    }

    m_nameList.removeRow(idx.row());

    m_db.deleteMove(name);
}

void MovesWindow::on_pushButton_Save_clicked()
{
    m_db.saveMoves();

    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void MovesWindow::on_pushButton_Cancel_clicked()
{
    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void MovesWindow::on_lineEdit_Name_editingFinished()
{
    const auto oldName = ui->listView->currentIndex().data().toString();
    const auto newName = ui->lineEdit_Name->text();
    if (oldName == newName) return;

    if (newName.isEmpty()) {
        ui->lineEdit_Name->setText(oldName);
        return;
    }

    m_nameList.setData(ui->listView->currentIndex(), newName);

    auto data = m_db.getMoves().at(oldName);
    assert(m_db.deleteMove(data.getName()));
    data.setName(newName);
    assert(m_db.insertMove(ui->listView->currentIndex().row() + 1, data));
}



void MovesWindow::on_lineEdit_BaseDamage_textChanged(const QString & arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    auto moves = m_db.getMoves();
    moves.at(name).setBaseDamage(arg1.toUInt());
    m_db.setMoves(moves);
}

void MovesWindow::on_lineEdit_Accuracy_textChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    auto moves = m_db.getMoves();
    moves.at(name).setAccuracy(arg1.toUInt());
    m_db.setMoves(moves);
}

void MovesWindow::on_lineEdit_Priority_textChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    auto moves = m_db.getMoves();
    moves.at(name).setPriority(arg1.toUInt());
    m_db.setMoves(moves);
}

void MovesWindow::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getMoves().empty()) return;

    const auto name = idx.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    auto moves = m_db.getMoves();
    moves.at(name).setType(arg1);
    m_db.setMoves(moves);
}

void MovesWindow::on_comboBox_Category_currentTextChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getMoves().empty()) return;

    const auto name = idx.data().toString();
    assert(m_db.getMoves().count(name) != 0);
    auto moves = m_db.getMoves();
    moves.at(name).setCategory(arg1);
    m_db.setMoves(moves);
}
