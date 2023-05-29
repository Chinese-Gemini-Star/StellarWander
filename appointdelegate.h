#ifndef APPOINTDELEGATE_H
#define APPOINTDELEGATE_H

#include <QItemDelegate>
#include "tourist.h"

class AppointDelegate : public QItemDelegate
{

    Q_OBJECT

public:
    explicit AppointDelegate(const QList<Tourist> &tourists, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

signals:
    void appointmentUpdate();

private:
    const QList<Tourist> &tourists;
};

#endif // APPOINTDELEGATE_H
