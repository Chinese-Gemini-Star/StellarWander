#include <QMessageBox>
#include <QRegularExpression>

#include "addtouristdialog.h"
#include "ui_addtouristdialog.h"
#include "tourist.h"
#include "databasetool.h"

AddTouristDialog::AddTouristDialog(const User &user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTouristDialog),
    user(user)
{
    ui->setupUi(this);
}

AddTouristDialog::~AddTouristDialog()
{
    delete ui;
}

void AddTouristDialog::on_okButton_clicked()
{
    qDebug() << "用户尝试添加游客" << Qt::endl;

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
    QRegularExpressionMatch idMatch = idRegex.match(ui->idEdit->text());
    if(!idMatch.hasMatch()) {
        qDebug() << "身份证号格式不正确" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "身份证号格式不正确");
        return;
    }

    Tourist tourist(ui->nameEdit->text(), ui->phoneEdit->text(), ui->idEdit->text());

    if(DatabaseTool::isTouristExist(tourist)) {
        if(DatabaseTool::isRelated(user,tourist)) {
            qDebug() << "重复添加同一游客" << Qt::endl;
            QMessageBox::warning(nullptr,"警告","该游客已被绑定");
            return;
        }
    } else {
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
    }
    DatabaseTool::setTourist(tourist);
    DatabaseTool::linkTouristToUser(user, tourist, false);
    accept();
}


void AddTouristDialog::on_cancelButton_clicked()
{
    reject();
}

