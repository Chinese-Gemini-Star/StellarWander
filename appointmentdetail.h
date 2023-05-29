#ifndef APPOINTMENTDETAIL_H
#define APPOINTMENTDETAIL_H

#include <QDialog>
#include <QdateTime>

#include "tourist.h"
#include "appointment.h"

namespace Ui {
class AppointmentDetail;
}

class AppointmentDetail : public QDialog
{
    Q_OBJECT

public:
    explicit AppointmentDetail(const Tourist &tourist, const Appointment &appointment, QWidget *parent = nullptr);
    ~AppointmentDetail();

private slots:
    void on_printButton_clicked();

    void on_deleteButton_clicked();

private:
    Tourist tourist;
    Appointment appointment;
    Ui::AppointmentDetail *ui;
};

#endif // APPOINTMENTDETAIL_H
