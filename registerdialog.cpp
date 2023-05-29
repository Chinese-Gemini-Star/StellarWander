#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "databaseTool.h"
#include "tourist.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_registerButton_clicked()
{
    // 未输入用户名
    if(ui->userNameEdit->text() == "") {
        qDebug() << "未输入用户名" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "未输入用户名");
        return;
    }

    // 用户名未以字母开头
    if(!ui->userNameEdit->text()[0].isLetter()) {
        qDebug() << "用户名未字母开头" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "用户名必须以字母开头");
        return;
    }

    // 未输入密码
    if(ui->passwordEdit->text() == "") {
        qDebug() << "未输入密码" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "未输入密码");
        return;
    }

    // 两次密码输入不一致
    if(ui->passwordEdit->text() != ui->checkPasswordEdit->text()) {
        qDebug() << "两次密码输入不一致" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "两次密码输入不一致");
        return;
    }

    // 未输入姓名
    if(ui->nameEdit->text() == "") {
        qDebug() << "未输入姓名" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "未输入姓名");
        return;
    }

    // 验证手机号合法性
    QRegularExpression phoneRegex("^1(3[0-9]|4[01456879]|5[0-35-9]|6[2567]|7[0-8]|8[0-9]|9[0-35-9])\\d{8}$");
    QRegularExpressionMatch phoneMatch = phoneRegex.match(ui->phoneEdit->text());
    if(!phoneMatch.hasMatch()) {
        qDebug() << "手机号格式不正确" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "手机号格式不正确");
        return;
    }

    // 验证身份证号合法性
    QRegularExpression idRegex("^[1-9]\\d{5}(19|20)\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    QRegularExpressionMatch idMatch = idRegex.match(ui->idEditor->text());
    if(!idMatch.hasMatch()) {
        qDebug() << "身份证号格式不正确" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "身份证号格式不正确");
        return;
    }

    User user(ui->userNameEdit->text(), ui->passwordEdit->text());
    // 检查用户名是否重复
    if(DatabaseTool::checkUserName(user)) {
        qDebug() << "用户名重复" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "该用户名已被使用");
        return;
    }

    Tourist tourist(ui->nameEdit->text(),ui->phoneEdit->text(),ui->idEditor->text());
    // 检查该游客是否被绑定
    if(DatabaseTool::checkSelf(tourist)) {
        qDebug() << "该游客已被绑定" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "该游客已被其他用户绑定为自身");
        return;
    }

    // 如果游客已存在,就不用写入
    if(!DatabaseTool::isTouristExist(tourist)) {
        // 部分信息重复
        if(DatabaseTool::checkId(tourist)) {
            qDebug() << "身份证号重复" << Qt::endl;
            QMessageBox::warning(nullptr,"警告","该身份证号已被另一个手机号对应的游客绑定");
            return;
        } else if(DatabaseTool::checkPhone(tourist)) {
            qDebug() << "手机号重复" << Qt::endl;
            QMessageBox::warning(nullptr,"警告","该手机号已被另一个身份证号对应的游客绑定");
            return;
        }
        DatabaseTool::setTourist(tourist);
    } else {
        qDebug() << "该游客已存在在数据库中,无需加入" << Qt::endl;
    }

    // 将用户写入数据库,并与游客绑定
    DatabaseTool::setUser(user);
    DatabaseTool::linkTouristToUser(user, tourist, true);
    qDebug() << "用户注册成功" << Qt::endl;
    emit registerSignals(user);
    accept();
}
