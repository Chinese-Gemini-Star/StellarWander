#ifndef DAYDELEGATE_H
#define DAYDELEGATE_H

#include <QItemDelegate>

class DayDelegate : public QItemDelegate
{
public:
    DayDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // DAYDELEGATE_H
