#include "typeswindow.h"
#include "ui_typeswindow.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QInputDialog>

#include <iostream>
#include <cassert>

TypesWindow::TypesWindow(const std::map<QString, std::shared_ptr<db::Database>> & map, db::Database & db, QWidget *parent) :
    QWidget(),
    DataWindow(parent, db, map),
    ui(new Ui::TypesWindow)
{
    ui->setupUi(this);

    QStringList list;
    const auto typesMap = m_db.getTypesByID();

    for (const auto & entry : typesMap) {

        list << entry.second.getName();

    }

    m_nameList.setStringList(list);

    ui->listView->setModel(&m_nameList);
    ui->listView->setCurrentIndex(m_nameList.index(0));
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox_Type->addItem("");
    ui->comboBox_Type->addItem("Zero");
    ui->comboBox_Type->addItem("HighlyIneffective");
    ui->comboBox_Type->addItem("Ineffective");
    ui->comboBox_Type->addItem("SlightlyIneffective");
    ui->comboBox_Type->addItem("Neutral");
    ui->comboBox_Type->addItem("SlightlyEffective");
    ui->comboBox_Type->addItem("Effective");
    ui->comboBox_Type->addItem("HighlyEffective");
    ui->comboBox_Type->addItem("MostEffective");

    ui->comboBox_Name->addItem("");
    for (const auto & type : list) {
        ui->comboBox_Name->addItem(type);
    }

    setCurrent(m_nameList.index(0));

    connect(ui->listView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(checkEntry(QModelIndex,QModelIndex)));

}

TypesWindow::~TypesWindow()
{
    delete ui;
}



void TypesWindow::setCurrent(const QModelIndex & current)
{

    if (!current.isValid()) return;

    const auto name = current.data().toString();
    assert(m_db.getTypes().count(name) != 0);
    const auto type = m_db.getTypes().at(name);

    ui->lineEdit_Name->setText(name);

    ui->comboBox_Name->setCurrentIndex(0);
    ui->comboBox_Type->setCurrentIndex(0);

    recalculate();

}

void TypesWindow::addNewEntry(const QString & name, unsigned int row)
{

    Type type;
    type.setName(name);
    type.setID(row + 1);

    assert(m_db.insertType(row + 1, type));

    ui->comboBox_Name->addItem(name);

}

void TypesWindow::recalculate() {

    const auto name = ui->listView->currentIndex().data().toString();
    if (m_db.getTypes().count(name) == 0) return;
    const auto type = m_db.getTypes().at(name);

    float atk = 0.f;
    for (const auto & t : type.effectivenesses()) {
        atk += Type::typeToFloat(t.second);
    }
    ui->label_Attack->setText(QString::number(atk, 'f', 2));

    float def = 0.f;
    for (const auto & t : m_db.getTypes()) {
        const auto effectivenesses = t.second.effectivenesses();
        if (effectivenesses.count(name) != 0) {
            def += Type::typeToFloat(effectivenesses.at(name));
        }
    }
    ui->label_Defense->setText(QString::number(def, 'f', 2));

    ui->label_Ratio->setText(QString::number(atk / def, 'f', 2));

}

void TypesWindow::setEmpty()
{

    ui->lineEdit_Name->setText("");

    ui->comboBox_Name->setCurrentIndex(0);
    ui->comboBox_Type->setCurrentIndex(0);

    ui->label_Attack->setText("0.00");
    ui->label_Defense->setText("0.00");
    ui->label_Ratio->setText("NaN");

}

void TypesWindow::checkEntry(const QModelIndex & current, const QModelIndex & previous) {

    DataWindow::checkEntry(current, previous);

}

void TypesWindow::on_pushButton_Add_clicked()
{

    bool ok;
    const auto text = QInputDialog::getText(this, "Type Editor", "Enter a name:", QLineEdit::Normal,
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

void TypesWindow::on_pushButton_Insert_clicked()
{

    bool ok;
    const auto text = QInputDialog::getText(this, "Type Editor", "Enter a name:", QLineEdit::Normal,
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

void TypesWindow::on_pushButton_Delete_clicked()
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

    m_db.deleteType(name);
}

void TypesWindow::on_pushButton_Save_clicked()
{
    m_db.saveTypes();

    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void TypesWindow::on_pushButton_Cancel_clicked()
{
    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void TypesWindow::on_lineEdit_Name_editingFinished()
{

    const auto oldName = ui->listView->currentIndex().data().toString();
    const auto newName = ui->lineEdit_Name->text();
    if (oldName == newName) return;

    if (newName.isEmpty()) {
        ui->lineEdit_Name->setText(oldName);
        return;
    }

    m_nameList.setData(ui->listView->currentIndex(), newName);

    auto data = m_db.getTypes().at(oldName);
    assert(m_db.deleteType(data.getName()));
    data.setName(newName);
    assert(m_db.insertType(ui->listView->currentIndex().row() + 1, data));
}

void TypesWindow::on_comboBox_Name_currentTextChanged(const QString & str)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getTypes().empty()) {
        // not initialized yet!
        return;
    }

    const auto name = idx.data().toString();
    assert(m_db.getTypes().count(name) != 0);

    const auto type = m_db.getTypes().at(name);
    if (type.effectivenesses().count(str) == 0) {
        // no effectiveness yet
        ui->comboBox_Type->setCurrentIndex(0);
    } else {
        ui->comboBox_Type->setCurrentText(Type::typeToString(type.effectivenesses().at(str)));
    }

}

void TypesWindow::on_comboBox_Type_currentTextChanged(const QString & str) {

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getTypes().empty()) return;

    const auto name = idx.data().toString();
    const auto effectType = ui->comboBox_Name->currentText();
    if (effectType.isEmpty()) return;

    auto types = m_db.getTypes();
    auto effectivenesses = types.at(name).effectivenesses();
    effectivenesses[effectType] = Type::stringToType(str);
    types.at(name).setEffectivenesses(effectivenesses);
    m_db.setTypes(types);

    recalculate();

}
