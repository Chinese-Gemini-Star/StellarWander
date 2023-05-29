#include <QMessageBox>
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_logindialog.h"
#include "databasetool.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_exitButton_clicked()
{
    reject();
}

void LoginDialog::on_loginButton_clicked()
{
    // 未输入用户名
    if(ui->userNameEdit->text() == "") {
        QMessageBox::warning(nullptr, "错误", "请输入用户名");
        qDebug() << "未输入用户名" << Qt::endl;
        return;
    }

    // 未输入密码
    if(ui->passwordEditor->text() == "") {
        QMessageBox::warning(nullptr, "错误", "请输入密码");
        qDebug() << "未输入密码" << Qt::endl;
        return;
    }

    // 用户名或密码错误
    if(DatabaseTool::getPasswordByUserName(ui->userNameEdit->text()) != ui->passwordEditor->text() && DatabaseTool::getPasswordByPhone(ui->userNameEdit->text()) != ui->passwordEditor->text()) {
        QMessageBox::warning(nullptr, "错误", "用户名或密码错误");
        return;
    }

    user = User(ui->userNameEdit->text(),ui->passwordEditor->text());
    accept();
}

User LoginDialog::getUser() {
    return user;
}

void LoginDialog::on_registerButton_clicked()
{
    RegisterDialog d;
    connect(&d,&RegisterDialog::registerSignals,this,&LoginDialog::getUserFromRegister);
    d.open();
    d.exec();
}


void LoginDialog::getUserFromRegister(User user) {
    ui->userNameEdit->setText(user.getUserName());
    ui->passwordEditor->setText(user.getPassword());
}
