#include "datawindow.h"

#include <iostream>

DataWindow::DataWindow(QWidget * parent, Database & db)
  : m_parent(parent),
    m_db(db)
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

