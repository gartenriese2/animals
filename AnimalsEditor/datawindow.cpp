#include "datawindow.h"

#include <iostream>

DataWindow::DataWindow(QWidget * parent, db::Database & db, const std::map<QString, std::shared_ptr<db::Database>> & map)
  : m_parent(parent),
    m_db(db),
    m_dbMap(map)
{

}

DataWindow::~DataWindow()
{

}

void DataWindow::checkEntry(const QModelIndex & current, const QModelIndex & previous) {

    // previous entry is invalid or empty
    if (!previous.data().isValid() || previous.data().toString().isEmpty()) {
        m_nameList.removeRow(previous.row());
    }

    // set current
    if (!current.data().toString().isEmpty()) {
        setCurrent(current);
    }

}

