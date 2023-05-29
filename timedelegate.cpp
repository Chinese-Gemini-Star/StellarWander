#include <QTimeEdit>
#include <QSqlTableModel>

#include "timedelegate.h"
TimeDelegate::TimeDelegate(QObject *parent)
    : QItemDelegate{parent}
{

}

QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTimeEdit *editor = new QTimeEdit(parent);
    editor->setDisplayFormat("hh:mm");
    return editor;
}

void TimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTimeEdit *dateEditor = qobject_cast<QTimeEdit *>(editor);
    if (dateEditor)
    {
        QTime time = QTime::fromString(index.data().toString(), "hh:mm");
        dateEditor->setTime(time);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *dateEditor = qobject_cast<QTimeEdit *>(editor);
    if (dateEditor)
    {
        QTime time = dateEditor->time();
        model->setData(index, time.toString("hh:mm"));
        qobject_cast<QSqlTableModel *>(model)->submitAll();
        qDebug() << "已完成对(" << index.row() << "," << index.column() << ")的修改,数据修改为" << time.toString("hhhh:mm") <<Qt::endl;
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}

