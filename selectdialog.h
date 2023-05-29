#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QDateTime>

#include "selectappointmentrule.h"

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(SelectAppointmentRule &rule, QWidget *parent = nullptr);
    ~SelectDialog();

signals:
    void selectSignals(SelectAppointmentRule rule);
private slots:
    void on_pushButton_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
