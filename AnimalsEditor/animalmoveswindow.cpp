#include "animalmoveswindow.h"
#include "ui_animalmoveswindow.h"

#include <QStringList>
#include <QSortFilterProxyModel>
#include <QList>
#include <QStandardItem>
#include <QDebug>

#include <cassert>

#include "database.h"
#include "comboboxdelegate.h"
#include "animaldatabase.h"

AnimalMovesWindow::AnimalMovesWindow(const std::map<QString, std::shared_ptr<db::Database>> & map, db::Database & db, const Animal & animal, QWidget * parent) :
    QWidget(),
    ui(new Ui::AnimalMovesWindow),
    m_parent(parent),
    m_db(db),
    m_dbMap(map),
    m_animal(animal)
{
    ui->setupUi(this);

    ui->label_Name->setText(m_animal.getName());

    QStringList horizontalHeader;
    horizontalHeader.append("Level");
    horizontalHeader.append("Move");
    horizontalHeader.append("Type");
    horizontalHeader.append("Category");
    horizontalHeader.append("Dmg");
    horizontalHeader.append("Acc");
    horizontalHeader.append("Prio");

    m_movesModel.setHorizontalHeaderLabels(horizontalHeader);

    ComboBoxDelegate * delegate = new ComboBoxDelegate(this);
    std::vector<QString> vec;
    for (const auto & move : m_db.getMovesByID()) {
        vec.emplace_back(move.second.getName());
    }
    delegate->setItems(vec);
    ui->tableView_Moves->setItemDelegateForColumn(1, delegate);

    QSortFilterProxyModel * proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(&m_movesModel);
    proxyModel->setSortRole(NumericModel::SortRole);

    ui->tableView_Moves->setModel(proxyModel);
    ui->tableView_Moves->resizeColumnsToContents();
    ui->tableView_Moves->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // calculate max move name size
    int size = 20;
    QFont font;
    QFontMetrics fm(font);
    for (const auto & move : m_db.getMoves()) {
        size = std::max(size, fm.width(move.first));
    }
    ui->tableView_Moves->horizontalHeader()->resizeSection(1, size + 30);

    // calculate max type name size
    size = 20;
    for (const auto & type : m_db.getTypes()) {
        size = std::max(size, fm.width(type.first));
    }
    ui->tableView_Moves->horizontalHeader()->resizeSection(2, size + 30);

    // fill moves
    for (const auto & p : m_animal.moves()) {

        assert(m_db.getMoves().count(p.second) != 0);
        const auto move = m_db.getMoves().at(p.second);
        QList<QStandardItem *> itemList;

        itemList.append(new QStandardItem(QString::number(p.first)));
        itemList.append(new QStandardItem(move.getName()));
        itemList.append(new QStandardItem(move.getType()));
        itemList.back()->setEditable(false);
        itemList.append(new QStandardItem(move.getCategory()));
        itemList.back()->setEditable(false);
        itemList.append(new QStandardItem(QString::number(move.getBaseDamage())));
        itemList.back()->setEditable(false);
        itemList.append(new QStandardItem(QString::number(move.getAccuracy())));
        itemList.back()->setEditable(false);
        itemList.append(new QStandardItem(QString::number(move.getPriority())));
        itemList.back()->setEditable(false);

        m_movesModel.appendRow(itemList);

    }

    connect(&m_movesModel, &QStandardItemModel::itemChanged, [&](QStandardItem * item){

        const auto col = item->column();

        if (col == 0) {

            // lvl changed
            ui->tableView_Moves->sortByColumn(0, Qt::AscendingOrder);

        } else if (col == 1) {

            // move changed
            const auto move = m_db.getMoves().at(item->text());
            m_movesModel.setItem(item->row(), 2, new QStandardItem(move.getType()));
            m_movesModel.setItem(item->row(), 3, new QStandardItem(move.getCategory()));
            m_movesModel.setItem(item->row(), 4, new QStandardItem(QString::number(move.getBaseDamage())));
            m_movesModel.setItem(item->row(), 5, new QStandardItem(QString::number(move.getAccuracy())));
            m_movesModel.setItem(item->row(), 6, new QStandardItem(QString::number(move.getPriority())));

        }

    });

}

AnimalMovesWindow::~AnimalMovesWindow()
{
    delete ui;
}

void AnimalMovesWindow::on_pushButton_Save_clicked()
{
    std::multimap<unsigned int, QString> moves;
    for (int r = 0; r < m_movesModel.rowCount(); ++r) {
        moves.emplace(m_movesModel.index(r, 0).data().toUInt(), m_movesModel.index(r, 1).data().toString());
    }
    m_animal.setMoves(moves);

    assert(dynamic_cast<db::AnimalDatabase *>(m_dbMap.at("Animals").get())->deleteData(m_animal.getName()));
//    assert(m_db.deleteAnimal(m_animal.getName()));
    assert(dynamic_cast<db::AnimalDatabase *>(m_dbMap.at("Animals").get())->insertData(m_animal.getID(), m_animal));
//    assert(m_db.insertAnimal(m_animal.getID(), m_animal));

    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();

}

void AnimalMovesWindow::on_pushButton_Cancel_clicked()
{
    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void AnimalMovesWindow::on_pushButton_AddMove_clicked()
{
    // chose arbitraty move -> todo: fix
    const auto move = *m_db.getMoves().begin();
    QList<QStandardItem *> itemList;
    itemList.append(new QStandardItem("1"));
    itemList.append(new QStandardItem(move.first));
    itemList.append(new QStandardItem(move.second.getType()));
    itemList.back()->setEditable(false);
    itemList.append(new QStandardItem(move.second.getCategory()));
    itemList.back()->setEditable(false);
    itemList.append(new QStandardItem(QString::number(move.second.getBaseDamage())));
    itemList.back()->setEditable(false);
    itemList.append(new QStandardItem(QString::number(move.second.getAccuracy())));
    itemList.back()->setEditable(false);
    itemList.append(new QStandardItem(QString::number(move.second.getPriority())));
    itemList.back()->setEditable(false);

    m_movesModel.appendRow(itemList);
    ui->tableView_Moves->sortByColumn(0, Qt::AscendingOrder);
}

void AnimalMovesWindow::on_pushButton_DeleteMove_clicked()
{
    auto idx = ui->tableView_Moves->currentIndex();
    assert(idx.isValid());

    const auto pm = static_cast<QSortFilterProxyModel *>(ui->tableView_Moves->model());
    const auto sourceIdx = pm->mapToSource(idx);

    m_movesModel.removeRow(sourceIdx.row());
}
