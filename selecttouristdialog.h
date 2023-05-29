#ifndef SELECTTOURISTDIALOG_H
#define SELECTTOURISTDIALOG_H

#include <QDialog>

#include "user.h"
#include "tourist.h"
#include "appointment.h"

namespace Ui {
class SelectTouristDialog;
}

class SelectTouristDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTouristDialog(const QList<Tourist> &tourists, const Appointment &appointment, QWidget *parent = nullptr);
    ~SelectTouristDialog();

private slots:
    void on_cancleButton_clicked();

    void on_selectButton_clicked();

private:
    Appointment appointment;
    QList<Tourist> tourists;
    Ui::SelectTouristDialog *ui;
};

#endif // SELECTTOURISTDIALOG_H
