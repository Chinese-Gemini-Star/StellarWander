#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QMessageBox>

#include "appointmentdetail.h"
#include "ui_appointmentdetail.h"
#include "databasetool.h"

AppointmentDetail::AppointmentDetail(const Tourist &tourist, const Appointment &appointment, QWidget *parent) :
    QDialog(parent),
    tourist(tourist),
    appointment(appointment),
    ui(new Ui::AppointmentDetail)
{
    ui->setupUi(this);

    ui->nameEdit->setText(tourist.getName());
    ui->phoneEdit->setText(tourist.getPhone());
    ui->idEdit->setText(tourist.getCardId());
    ui->dayEdit->setDate(appointment.getDay());
    ui->startTimeEdit->setDateTime(appointment.getStartTime());
    ui->endTimeEdit->setDateTime(appointment.getEndTime());
}

AppointmentDetail::~AppointmentDetail()
{
    delete ui;
}

void AppointmentDetail::on_printButton_clicked()
{
    // 选择保存路径
    QString filePath = QFileDialog::getSaveFileName(nullptr, "保存预约信息", "预约信息", "*.pdf");
    if (filePath.isEmpty())
        return;

    // 创建打印机
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(this->size() * this->devicePixelRatio()));

    // 创建绘制器
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 绘制界面到绘制器上
    this->render(&painter);

    // 提示保存成功
    QMessageBox::information(nullptr, "保存成功", "预约信息保存成功");
}

void AppointmentDetail::on_deleteButton_clicked()
{
    QMessageBox::StandardButton res = QMessageBox::question(this, "删除确认", "您确定要取消吗?",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes) {
        qDebug() << "用户确认了删除操作" << Qt::endl;
        DatabaseTool::disappoint(tourist,appointment);
        reject();
    }
}

