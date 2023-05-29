#include <QDate>
#include <QMessageBox>

#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "newappointmentdialog.h"
#include "selectdialog.h"
#include "detaildialog.h"
#include "daydelegate.h"
#include "readonlydelegate.h"
#include "timedelegate.h"

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);

    ui->appointmentInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = ui->appointmentInfo->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    ui->appointmentInfo->setSizePolicy(policy);

    // 绑定委托
    DayDelegate *dayDelegate = new DayDelegate(ui->appointmentInfo);
    ui->appointmentInfo->setItemDelegateForColumn(0,dayDelegate);
    TimeDelegate *timeDelegate = new TimeDelegate(ui->appointmentInfo);
    ui->appointmentInfo->setItemDelegateForColumn(1,timeDelegate);
    ui->appointmentInfo->setItemDelegateForColumn(2,timeDelegate);
    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(ui->appointmentInfo);
    ui->appointmentInfo->setItemDelegateForColumn(4,readOnlyDelegate);

    bindData();

    // 初始显示3天内的信息
    on_threeAction_triggered();
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::bindData() {
    // 打开数据表
    appointmentInfo.setTable("appointments");

    // 设置各列标题
    appointmentInfo.setHeaderData(0, Qt::Horizontal, "日期");
    appointmentInfo.setHeaderData(1, Qt::Horizontal, "开始时间");
    appointmentInfo.setHeaderData(2, Qt::Horizontal, "结束时间");
    appointmentInfo.setHeaderData(3, Qt::Horizontal, "人数上限");
    appointmentInfo.setHeaderData(4, Qt::Horizontal, "已预约人数");

    ui->appointmentInfo->setModel(&appointmentInfo);

    // 隐藏主键列
    ui->appointmentInfo->hideColumn(5);
}

void AdminMainWindow::selectDate(const SelectAppointmentRule where) {
    // 保存当前查询规则,以便实现刷新
    prevWhere = where;

    // 设置查询条件
    QString select = QString("day>=\"%1\" AND day<=\"%2\" AND time_start>=\"%3\" AND time_end<=\"%4\"")
                         .arg(prevWhere.getStartDay().toString("yyyy/MM/dd"))
                         .arg(prevWhere.getEndDay().toString("yyyy/MM/dd"))
                         .arg(prevWhere.getStartTime().toString("hh:mm"))
                         .arg(prevWhere.getEndTime().toString("hh:mm"));
    if(prevWhere.getNumLimitS() != -1) {
        select += QString("AND numLimit>=\"%1\"").arg(prevWhere.getNumLimitS());
    }
    if(prevWhere.getNumLimitE() != -1) {
        select += QString("AND numLimit<=\"%1\"").arg(prevWhere.getNumLimitE());
    }
    if(prevWhere.getNumS() != -1) {
        select += QString("AND num >= \"%1\"").arg(prevWhere.getNumS());
    }
    if(prevWhere.getNumE() != -1) {
        select += QString("AND num <= \"%1\"").arg(prevWhere.getNumE());
    }
    qDebug() << "执行了查询:" << select << Qt::endl;
    appointmentInfo.setFilter(select);

    // 设置排序规则
    appointmentInfo.setSort(1,Qt::AscendingOrder);
    appointmentInfo.setSort(2,Qt::AscendingOrder);
    appointmentInfo.select();
}

void AdminMainWindow::selectDate() {
    selectDate(prevWhere);
}

void AdminMainWindow::on_newAction_triggered() {
    newAppointmentDialog newDialog;
    newDialog.open();
    if(newDialog.exec() == QDialog::Accepted) {
        selectDate();
    }
}

void AdminMainWindow::on_deleteAction_triggered() {
    // 未选中元素,不支持删除
    if(!ui->appointmentInfo->currentIndex().isValid()) {
        QMessageBox::warning(nullptr,"警告","当前未选中任何元素");
        qDebug() << "管理员未选中行而执行删除" << Qt::endl;
        return;
    }
    QMessageBox::StandardButton res = QMessageBox::question(this, "删除确认", "您确定要删除吗?",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes) {
        qDebug() << "管理员确认了删除操作" << Qt::endl;
        for(auto i : ui->appointmentInfo->selectionModel()->selectedIndexes()) {
            int row = i.row();

            // 已有人预约
            if(appointmentInfo.index(row,4).data().toInt()) {
                qDebug() << "管理员试图删除已有人预约的时间段" << Qt::endl;
                res = QMessageBox::question(this, "预约保护", QString("于%1的从%2到%3的时间段已有人预约,不可删除.是否要把可预约人数上限设置成当前已预约人数?")
                    .arg(appointmentInfo.index(row,0).data().toString())
                    .arg(appointmentInfo.index(row,1).data().toString())
                    .arg(appointmentInfo.index(row,2).data().toString()),
                    QMessageBox::Yes | QMessageBox::No);
                if(res == QMessageBox::Yes) {
                    appointmentInfo.setData(appointmentInfo.index(row,3),appointmentInfo.index(row,4).data().toInt());
                    qDebug() << "管理员确认了把人数设置成上限" << Qt::endl;
                } else {
                    qDebug() << "管理员取消了把人数设置成上限" << Qt::endl;
                }
            } else {
                appointmentInfo.removeRow(row);
            }
        }
        appointmentInfo.submitAll();
        selectDate();
    } else {
        qDebug() << "管理员取消了删除操作" << Qt::endl;
    }
}

void AdminMainWindow::on_todayAction_triggered() {
    selectDate(SelectAppointmentRule());
}

void AdminMainWindow::on_threeAction_triggered() {
    QDate now = QDate::currentDate();
    QDate limit = QDate::currentDate().addDays(2);
    selectDate(SelectAppointmentRule(now, limit));
}

void AdminMainWindow::on_weekAction_triggered() {
    QDate now = QDate::currentDate();
    QDate limit = QDate::currentDate().addDays(6);
    selectDate(SelectAppointmentRule(now,limit));
}

void AdminMainWindow::on_monthAction_triggered() {
    QDate now = QDate::currentDate();
    QDate limit = QDate::currentDate().addMonths(1).addDays(-1);
    selectDate(SelectAppointmentRule(now,limit));
}

void AdminMainWindow::on_selectAction_triggered() {
    SelectDialog selectDialog(prevWhere);
    selectDialog.open();
    connect(&selectDialog,&SelectDialog::selectSignals,this,QOverload<SelectAppointmentRule>::of(&AdminMainWindow::selectDate));
    selectDialog.exec();
}


void AdminMainWindow::on_detailAction_triggered() {
    // 未选中元素,不支持删除
    if(!ui->appointmentInfo->currentIndex().isValid()) {
        QMessageBox::warning(nullptr,"警告","当前未选中任何元素");
        qDebug() << "管理员未选中行而执行删除" << Qt::endl;
        return;
    }

    int id = appointmentInfo.data(appointmentInfo.index(ui->appointmentInfo->currentIndex().row(),5)).toInt();
    qDebug() << "管理员查询了id为" << id << "的预约时间" <<Qt::endl;
    DetailDialog detailDialog(id);
    detailDialog.show();
    detailDialog.exec();
}
