#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QWidget>
#include <QStringListModel>
#include <QModelIndex>
#include <QString>

#include <map>
#include <memory>

#include "database.h"

class DataWindow {

    public:
        DataWindow(QWidget *, db::Database &, const std::map<QString, std::shared_ptr<db::Database>> &);
        virtual ~DataWindow();

    protected:

        QWidget * m_parent;

        QStringListModel m_nameList;
        db::Database & m_db;
        std::map<QString, std::shared_ptr<db::Database>> m_dbMap;

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
