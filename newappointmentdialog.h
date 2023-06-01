#ifndef NEWAPPOINTMENTDIALOG_H
#define NEWAPPOINTMENTDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class NewAppointmentDialog;
}

class NewAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAppointmentDialog(QWidget *parent = nullptr);
    ~NewAppointmentDialog();

private slots:
    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::NewAppointmentDialog *ui;
};

#endif // NEWAPPOINTMENTDIALOG_H
