#include <QMessageBox>

#include "newappointmentdialog.h"
#include "ui_newappointmentdialog.h"
#include "databasetool.h"
#include "appointment.h"

newAppointmentDialog::newAppointmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newAppointmentDialog)
{
    ui->setupUi(this);

    // 设置输入框默认值
    ui->dayEdit->setDateTime(QDateTime::currentDateTime());
    ui->startTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));
}

newAppointmentDialog::~newAppointmentDialog()
{
    delete ui;
}

void newAppointmentDialog::on_saveButton_clicked()
{
    // 未输入人数上限
    if(ui->numLimitEdit->text() == "") {
        qDebug() << "管理员未输入人数上限" << Qt::endl;
        QMessageBox::warning(nullptr,"警告","请输入人数上限");
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

void newAppointmentDialog::on_closeButton_clicked()
{
    reject();
}
