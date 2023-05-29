#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_exitButton_clicked();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::LoginDialog *ui;
    User user;
    void getUserFromRegister(User user);

public:
    User getUser();
};

#endif // LOGINDIALOG_H
