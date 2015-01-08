#include "animalswindow.h"
#include "ui_animalswindow.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QInputDialog>
#include <QList>

#include <QDebug>
#include <cassert>

constexpr unsigned int k_minVal {0};
constexpr unsigned int k_maxVal {200};

AnimalsWindow::AnimalsWindow(Database & db, QWidget *parent) :
    QWidget(),
    DataWindow(parent, db),
    ui(new Ui::AnimalsWindow)
{
    ui->setupUi(this);

    init();

    setCurrent(m_nameList.index(0));

    connect(ui->listView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(checkEntry(QModelIndex,QModelIndex)));

}

AnimalsWindow::~AnimalsWindow()
{
    delete ui;
}

void AnimalsWindow::init() {

    QValidator * validator = new QIntValidator(k_minVal, k_maxVal, this);
    ui->lineEdit_HP->setValidator(validator);
    ui->lineEdit_Attack->setValidator(validator);
    ui->lineEdit_Defense->setValidator(validator);
    ui->lineEdit_Speed->setValidator(validator);
    ui->lineEdit_SpecialAttack->setValidator(validator);
    ui->lineEdit_SpecialDefense->setValidator(validator);
    ui->lineEdit_BaseXP->setValidator(validator);

    ui->progressBar_HP->setTextVisible(false);
    ui->progressBar_Attack->setTextVisible(false);
    ui->progressBar_Defense->setTextVisible(false);
    ui->progressBar_Speed->setTextVisible(false);
    ui->progressBar_SpecialAttack->setTextVisible(false);
    ui->progressBar_SpecialDefense->setTextVisible(false);

    QStringList list;
    const auto animalsMap = m_db.getAnimalsByID();
    for (const auto & entry : animalsMap) {

        list << entry.second.getName();

    }
    m_nameList.setStringList(list);

    ui->listView->setModel(&m_nameList);
    ui->listView->setCurrentIndex(m_nameList.index(0));
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox_Primary->addItem("");
    ui->comboBox_Secondary->addItem("");
    for (const auto & type : m_db.getTypesByID()) {
        ui->comboBox_Primary->addItem(type.second.getName());
        ui->comboBox_Secondary->addItem(type.second.getName());
    }

}

void AnimalsWindow::setCurrent(const QModelIndex & current)
{

    if (!current.isValid()) return;

    const auto name = current.data().toString();
    assert(m_db.getAnimals().count(name) != 0);
    const auto animal = m_db.getAnimals().at(name);

    ui->lineEdit_Name->setText(name);

    ui->comboBox_Primary->setCurrentText(animal.primaryType());
    ui->comboBox_Secondary->setCurrentText(animal.secondaryType());

    ui->lineEdit_HP->setText(QString::number(animal.baseHP()));
    ui->lineEdit_Attack->setText(QString::number(animal.baseAttack()));
    ui->lineEdit_Defense->setText(QString::number(animal.baseDefense()));
    ui->lineEdit_Speed->setText(QString::number(animal.baseSpeed()));
    ui->lineEdit_SpecialAttack->setText(QString::number(animal.baseSpecialAttack()));
    ui->lineEdit_SpecialDefense->setText(QString::number(animal.baseSpecialDefense()));
    ui->lineEdit_BaseXP->setText(QString::number(animal.baseXP()));

    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));

}

void AnimalsWindow::addNewEntry(const QString & name, unsigned int row)
{

    Animal animal;
    animal.setName(name);
    animal.setID(row + 1);

    assert(m_db.insertAnimal(row + 1, animal));

}

void AnimalsWindow::setEmpty()
{

    ui->lineEdit_Name->setText("");

    ui->comboBox_Primary->setCurrentIndex(0);
    ui->comboBox_Secondary->setCurrentIndex(0);

    ui->lineEdit_HP->setText("0");
    ui->lineEdit_Attack->setText("0");
    ui->lineEdit_Defense->setText("0");
    ui->lineEdit_Speed->setText("0");
    ui->lineEdit_SpecialAttack->setText("0");
    ui->lineEdit_SpecialDefense->setText("0");
    ui->lineEdit_BaseXP->setText("0");
    ui->label_Total->setText("0");

}

void AnimalsWindow::checkEntry(const QModelIndex & current, const QModelIndex & previous) {

    DataWindow::checkEntry(current, previous);

}

void AnimalsWindow::on_pushButton_Add_clicked()
{

    bool ok;
    const auto text = QInputDialog::getText(this, "Animal Editor", "Enter a name:", QLineEdit::Normal,
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

void AnimalsWindow::on_pushButton_Insert_clicked()
{

    bool ok;
    const auto text = QInputDialog::getText(this, "Animal Editor", "Enter a name:", QLineEdit::Normal,
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

void AnimalsWindow::on_pushButton_Delete_clicked()
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

    m_db.deleteAnimal(name);
}

void AnimalsWindow::on_pushButton_Save_clicked()
{
    m_db.saveAnimals();

    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void AnimalsWindow::on_pushButton_Cancel_clicked()
{
    m_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void AnimalsWindow::on_lineEdit_Name_editingFinished()
{
    const auto oldName = ui->listView->currentIndex().data().toString();
    const auto newName = ui->lineEdit_Name->text();
    if (oldName == newName) return;

    if (newName.isEmpty()) {
        ui->lineEdit_Name->setText(oldName);
        return;
    }

    m_nameList.setData(ui->listView->currentIndex(), newName);

    auto data = m_db.getAnimals().at(oldName);
    assert(m_db.deleteAnimal(data.getName()));
    data.setName(newName);
    assert(m_db.insertAnimal(ui->listView->currentIndex().row() + 1, data));
}

void AnimalsWindow::on_lineEdit_HP_textChanged(const QString & arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_HP->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    assert(m_db.getAnimals().count(name) != 0);
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseHP(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_Attack_textChanged(const QString & arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_Attack->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseAttack(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_Defense_textChanged(const QString &arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_Defense->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseDefense(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_Speed_textChanged(const QString &arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_Speed->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseSpeed(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_SpecialAttack_textChanged(const QString &arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_SpecialAttack->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseSpecialAttack(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_SpecialDefense_textChanged(const QString &arg1)
{
    float percent = arg1.toFloat() / static_cast<float>(k_maxVal) * 100.f;
    ui->progressBar_SpecialDefense->setValue(static_cast<unsigned int>(percent));

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseSpecialDefense(arg1.toUInt());
    m_db.setAnimals(animals);

    const auto animal = animals.at(name);
    unsigned int sum = animal.baseHP() + animal.baseAttack() + animal.baseDefense() + animal.baseSpeed() +
            animal.baseSpecialAttack() + animal.baseSpecialDefense();
    ui->label_Total->setText(QString::number(sum));
}

void AnimalsWindow::on_lineEdit_BaseXP_textChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    const auto name = idx.data().toString();
    if (m_db.getAnimals().count(name) == 0) return;
    auto animals = m_db.getAnimals();
    animals.at(name).setBaseXP(arg1.toUInt());
    m_db.setAnimals(animals);
}

void AnimalsWindow::on_comboBox_Secondary_currentTextChanged(const QString &arg1)
{
    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getAnimals().empty()) return;

    const auto name = idx.data().toString();
    assert(m_db.getAnimals().count(name) != 0);
    auto animals = m_db.getAnimals();
    animals.at(name).setSecondaryType(arg1);
    m_db.setAnimals(animals);
}

void AnimalsWindow::on_comboBox_Primary_currentTextChanged(const QString &arg1)
{
    if (arg1 == "") return; // has to have a primary type!

    const auto idx = ui->listView->currentIndex();
    if (!idx.isValid()) return;

    if (m_db.getAnimals().empty()) return;

    const auto name = idx.data().toString();
    assert(m_db.getAnimals().count(name) != 0);
    auto animals = m_db.getAnimals();
    animals.at(name).setPrimaryType(arg1);
    m_db.setAnimals(animals);
}

void AnimalsWindow::on_pushButton_EditMoves_clicked()
{
    const auto idx = ui->listView->currentIndex();
    const auto animals = m_db.getAnimals();
    const auto animal = animals.at(idx.data().toString());
    m_editMovesWin = new AnimalMovesWindow(m_db, animal, this);
    m_editMovesWin->show();
    this->hide();
}
