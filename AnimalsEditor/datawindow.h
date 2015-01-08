#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QWidget>
#include <QStringListModel>
#include <QModelIndex>
#include <QString>

#include "database.h"

class DataWindow {

    public:
        DataWindow(QWidget *, Database &);
        virtual ~DataWindow();

    protected:

        QWidget * m_parent;

        QStringListModel m_nameList;
        Database & m_db;

        virtual void setCurrent(const QModelIndex &) = 0;
        virtual void addNewEntry(const QString &, unsigned int) = 0;

    protected slots:

        virtual void checkEntry(const QModelIndex &, const QModelIndex &);
        virtual void on_pushButton_Add_clicked() = 0;
        virtual void on_pushButton_Delete_clicked() = 0;
        virtual void on_pushButton_Save_clicked() = 0;
        virtual void on_pushButton_Cancel_clicked() = 0;
        virtual void on_lineEdit_Name_editingFinished() = 0;

};

#endif // DATAWINDOW_H
