#ifndef ADDTOURISTDIALOG_H
#define ADDTOURISTDIALOG_H

#include <QDialog>

#include "user.h"

namespace Ui {
class AddTouristDialog;
}

class AddTouristDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTouristDialog(const User &user, QWidget *parent = nullptr);
    ~AddTouristDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddTouristDialog *ui;
    User user;
};

#endif // ADDTOURISTDIALOG_H
