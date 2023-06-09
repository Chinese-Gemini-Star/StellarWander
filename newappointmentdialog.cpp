#include <QMessageBox>

#include "newappointmentdialog.h"
#include "ui_newappointmentdialog.h"
#include "databasetool.h"
#include "appointment.h"

NewAppointmentDialog::NewAppointmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAppointmentDialog)
{
    ui->setupUi(this);

    // 设置输入框默认值
    ui->dayEdit->setDateTime(QDateTime::currentDateTime());
    ui->startTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));
}

NewAppointmentDialog::~NewAppointmentDialog()
{
    delete ui;
}

void NewAppointmentDialog::on_saveButton_clicked()
{
    if(ui->startTimeEdit->dateTime() >= ui->endTimeEdit->dateTime()) {
        qDebug() << "管理员指定的时间范围不合法" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "请输入正确的时间范围");
        return;
    }

    if(ui->startTimeEdit->dateTime().addSecs(3600 / 2) > ui->endTimeEdit->dateTime()) {
        qDebug() << "管理给定的时间范围太小" << Qt::endl;
        QMessageBox::warning(nullptr, "警告", "可预约的时间段至少持续30分钟");
        return;
    }

    // 未输入人数上限
    if(ui->numLimitEdit->text().toInt() <= 0) {
        qDebug() << "管理员未输入正确的人数上限" << Qt::endl;
        QMessageBox::warning(nullptr,"警告","请输入正确的人数上限");
        return;
    }

    Appointment appointment(ui->dayEdit->date(), ui->startTimeEdit->dateTime(), ui->endTimeEdit->dateTime(),ui->numLimitEdit->text().toInt());

    // 重复添加
    if(DatabaseTool::checkAppointment(appointment)) {
        qDebug() << "管理员重复添加可预约时间" << Qt::endl;
        QMessageBox::warning(this, "可预约时间冲突", "当前完全相同的可预约时间段已经存在,不可设置");
        return;
    }
    DatabaseTool::setAppointment(appointment);
    accept();
}

void NewAppointmentDialog::on_closeButton_clicked()
{
    reject();
}
