#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDateTime>

#include "appointdelegate.h"
#include "appointment.h"
#include "appointmentdetail.h"
#include "selecttouristdialog.h"

AppointDelegate::AppointDelegate(const QList<Tourist> &tourists, QObject *parent)
    : QItemDelegate(parent),tourists(tourists)
{}

void AppointDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton buttonOption;
    buttonOption.rect = option.rect;
    buttonOption.text = "预约";
    buttonOption.state = QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
}

bool AppointDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (option.rect.contains(mouseEvent->pos()))
        {
            Appointment appointment(QDate::fromString(model->index(index.row(),0).data().toString(),"yyyy/MM/dd"),QDateTime::fromString(model->index(index.row(),1).data().toString(),"hh:mm"),QDateTime::fromString(model->index(index.row(),2).data().toString(),"hh:mm"), model->index(index.row(),3).data().toInt(), model->index(index.row(),5).data().toInt(), model->index(index.row(),4).data().toInt());
            SelectTouristDialog selectTouristDialog(tourists,appointment);
            selectTouristDialog.open();

            // 预约了用户对应的游客本身
            if(selectTouristDialog.exec() == QDialog::Accepted) {
                qDebug() << "选中了用户本身对应的游客 " << Qt::endl;
                AppointmentDetail appointmentDetail(tourists[0],appointment);
                appointmentDetail.show();
                appointmentDetail.exec();
            }
            emit appointmentUpdate();
            return true;
        }
    }

    return false;
}
