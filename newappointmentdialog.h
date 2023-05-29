#ifndef NEWAPPOINTMENTDIALOG_H
#define NEWAPPOINTMENTDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class newAppointmentDialog;
}

class newAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newAppointmentDialog(QWidget *parent = nullptr);
    ~newAppointmentDialog();

private slots:
    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::newAppointmentDialog *ui;
};

#endif // NEWAPPOINTMENTDIALOG_H
