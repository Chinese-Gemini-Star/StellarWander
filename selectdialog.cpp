#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(SelectAppointmentRule &rule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);

    // 默认显示为上一次的查询
    ui->startDayEdit->setDate(rule.getStartDay());
    ui->endDayEdit->setDate(rule.getEndDay());
    ui->startTimeEdit->setDateTime(rule.getStartTime());
    ui->endTimeEdit->setDateTime(rule.getEndTime());
    ui->limitNumSEdit->setText(QString::number(rule.getNumLimitS()) == "-1" ? "" : QString::number(rule.getNumLimitS()));
    ui->limitNumEEdit->setText(QString::number(rule.getNumLimitE()) == "-1" ? "" : QString::number(rule.getNumLimitE()));
    ui->numSEdit->setText(QString::number(rule.getNumS()) == "-1" ? "" : QString::number(rule.getNumS()));
    ui->numEEdit->setText(QString::number(rule.getNumE()) == "-1" ? "" : QString::number(rule.getNumE()));
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_pushButton_clicked()
{
    // 处理无限制
    if(ui->limitNumSEdit->text() == "") {
        ui->limitNumSEdit->setText("-1");
    }
    if(ui->limitNumEEdit->text() == "") {
        ui->limitNumEEdit->setText("-1");
    }
    if(ui->numSEdit->text() == "") {
        ui->numSEdit->setText("-1");
    }
    if(ui->numEEdit->text() == "") {
        ui->numEEdit->setText("-1");
    }

    SelectAppointmentRule rule(ui->startDayEdit->date(),
                               ui->endDayEdit->date(),
                               ui->startTimeEdit->dateTime(),
                               ui->endTimeEdit->dateTime(),
                               ui->limitNumSEdit->text().toInt(),
                               ui->limitNumEEdit->text().toInt(),
                               ui->numSEdit->text().toInt(),
                               ui->numEEdit->text().toInt());
    emit selectSignals(rule);
    accept();
}

