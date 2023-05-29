#include <qapplication.h>
#include <QMouseEvent>
#include <qdatetime.h>

#include "appointmentdetaildelegate.h"
#include "appointment.h"
#include "appointmentdetail.h"

AppointmentDetailDelegate::AppointmentDetailDelegate(const Tourist &tourist, QObject *parent)
    : QItemDelegate(parent),tourist(tourist)
{}

void AppointmentDetailDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton buttonOption;
    buttonOption.rect = option.rect;
    buttonOption.text = "查看详情";
    buttonOption.state = QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
}

bool AppointmentDetailDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (option.rect.contains(mouseEvent->pos()))
        {
            Appointment appointment(QDate::fromString(model->index(index.row(),0).data().toString(),"yyyy/MM/dd"),QDateTime::fromString(model->index(index.row(),1).data().toString(),"hh:mm"),QDateTime::fromString(model->index(index.row(),2).data().toString(),"hh:mm"), model->index(index.row(),3).data().toInt(), model->index(index.row(),5).data().toInt(), model->index(index.row(),4).data().toInt());

            qDebug() << "用户查看id为" << appointment.getId() << "的时间段的预约详情" << Qt::endl;
            AppointmentDetail appointmentDetail(tourist,appointment);
            appointmentDetail.show();
            appointmentDetail.exec();
            emit appointmentUpdate();
            return true;
        }
    }

    return false;
}
