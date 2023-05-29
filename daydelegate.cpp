#include <QDateEdit>
#include <QSqlTableModel>

#include "daydelegate.h"

DayDelegate::DayDelegate(QObject *parent) : QItemDelegate(parent) {}

QWidget *DayDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *editor = new QDateEdit(parent);
    editor->setDisplayFormat("yyyy/MM/dd");
    return editor;
}

void DayDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDateEdit *dateEditor = qobject_cast<QDateEdit *>(editor);
    if (dateEditor)
    {
        QDate date = QDate::fromString(index.data().toString(), "yyyy/MM/dd");
        dateEditor->setDate(date);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void DayDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateEdit *dateEditor = qobject_cast<QDateEdit *>(editor);
    if (dateEditor)
    {
        QDate date = dateEditor->date();
        model->setData(index, date.toString("yyyy/MM/dd"));
        qobject_cast<QSqlTableModel *>(model)->submitAll();
        qDebug() << "已完成对(" << index.row() << "," << index.column() << ")的修改,数据修改为" << date.toString("yyyy/MM/dd") <<Qt::endl;
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}
