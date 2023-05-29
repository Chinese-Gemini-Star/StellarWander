#ifndef APPOINTMENTDETAILDELEGATE_H
#define APPOINTMENTDETAILDELEGATE_H

#include <QItemDelegate>

#include "tourist.h"

class AppointmentDetailDelegate : public QItemDelegate
{

    Q_OBJECT

public:
    explicit AppointmentDetailDelegate(const Tourist &tourist, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

signals:
    void appointmentUpdate();

private:
    const Tourist &tourist;
};

#endif // APPOINTMENTDETAILDELEGATE_H
