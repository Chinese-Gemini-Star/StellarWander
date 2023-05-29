#include <QStackedLayout>
#include <QSqlTableModel>
#include <QDateTime>
#include <QStandardItemModel>
#include <QMessageBox>

#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include "databasetool.h"
#include "addtouristdialog.h"
#include "appointdelegate.h"
#include "appointmentdetaildelegate.h"

UserMainWindow::UserMainWindow(const User &user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow),
    user(user)
{
    ui->setupUi(this);

    // 初始化游客信息
    initTourists();

    ui->contents->insertItem(0,"查看已预约时间");
    ui->contents->insertItem(1,"预约浏览时间");
    ui->contents->insertItem(2,"管理已绑定的游客");
    ui->contents->item(0)->setSelected(true);

    connect(ui->contents,&QListWidget::currentRowChanged,ui->mainWidget,&QStackedWidget::setCurrentIndex);

    update();
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::update() {
    initAppointmentAvailable();
    initAppointmentReserved();
}

void UserMainWindow::initAppointmentReserved() {
    QTableView *appointmentReservedTableView = ui->mainWidget->widget(0)->findChild<QTableView *>("appointmentAvailableTableView");

    delete appointmentReservedTableView->model();

    // 打开数据表
    QSqlTableModel *appointments = new QSqlTableModel();
    appointments->setTable("appointments");

    // 设置各列标题
    appointments->setHeaderData(0, Qt::Horizontal, "日期");
    appointments->setHeaderData(1, Qt::Horizontal, "开始时间");
    appointments->setHeaderData(2, Qt::Horizontal, "结束时间");
    appointments->setHeaderData(3, Qt::Horizontal, "人数上限");
    appointments->setHeaderData(4, Qt::Horizontal, "已预约人数");
    appointments->setHeaderData(5,Qt::Horizontal, "");

    appointments->setFilter(QString("id in (SELECT appointmentId FROM tourist_appointment_informations WHERE touristId=\"%1\")")
                                .arg(tourists[0].getCardId()));
    appointments->select();

    appointmentReservedTableView->setModel(appointments);

    // 通过委托把主键列换成预约键
    delete appointmentReservedTableView->itemDelegateForColumn(5);
    AppointmentDetailDelegate *appointetailDelegate = new AppointmentDetailDelegate(tourists[0], appointments);
    appointmentReservedTableView->setItemDelegateForColumn(5,appointetailDelegate);
    connect(appointetailDelegate, &AppointmentDetailDelegate::appointmentUpdate,this, &UserMainWindow::update);

    appointmentReservedTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = appointmentReservedTableView->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    appointmentReservedTableView->setSizePolicy(policy);
    appointmentReservedTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserMainWindow::initAppointmentAvailable() {
    QTableView *appointmentAvailableTableView = ui->mainWidget->widget(1)->findChild<QTableView *>("appointmentReservedTableView");

    delete appointmentAvailableTableView->model();

    // 打开数据表
    QSqlTableModel *appointments = new QSqlTableModel();
    appointments->setTable("appointments");

    // 设置各列标题
    appointments->setHeaderData(0, Qt::Horizontal, "日期");
    appointments->setHeaderData(1, Qt::Horizontal, "开始时间");
    appointments->setHeaderData(2, Qt::Horizontal, "结束时间");
    appointments->setHeaderData(3, Qt::Horizontal, "人数上限");
    appointments->setHeaderData(4, Qt::Horizontal, "已预约人数");
    appointments->setHeaderData(5, Qt::Horizontal, "");

    QDate now = QDate::currentDate();

    appointments->setFilter(QString("day >= \"%1\" AND day <= \"%2\"")
                                .arg(now.toString("yyyy/MM/dd")).arg(now.addDays(1).toString("yyyy/MM/dd")));
    appointments->select();

    appointmentAvailableTableView->setModel(appointments);

    // 通过委托把主键列换成预约键
    delete appointmentAvailableTableView->itemDelegateForColumn(5);
    AppointDelegate *appointDelegate = new AppointDelegate(tourists, appointments);
    appointmentAvailableTableView->setItemDelegateForColumn(5,appointDelegate);
    connect(appointDelegate, &AppointDelegate::appointmentUpdate,this, &UserMainWindow::update);

    appointmentAvailableTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = appointmentAvailableTableView->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    appointmentAvailableTableView->setSizePolicy(policy);
    appointmentAvailableTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserMainWindow::initTourists() {
    DatabaseTool::getTouristsByUser(user,tourists);
    QTableView *touristsTableView = ui->mainWidget->widget(2)->findChild<QTableView *>("touristsTableView");

    delete touristsTableView->model();

    // 初始化模型
    QStandardItemModel *tourists = new QStandardItemModel();
    tourists->setHorizontalHeaderLabels(QStringList() << "姓名" << "电话" << "身份证号");

    for(const auto &i : this->tourists) {
        tourists->appendRow(QList<QStandardItem *>() << new QStandardItem(i.getName()) << new QStandardItem(i.getPhone()) << new QStandardItem(i.getCardId()));
    }

    touristsTableView->setModel(tourists);

    touristsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = touristsTableView->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    touristsTableView->setSizePolicy(policy);
    touristsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserMainWindow::on_addButton_clicked()
{

    if(tourists.size() >= 5) {
        QMessageBox::warning(nullptr,"警告","可绑定用户数已达到上限");
        return;
    }

    AddTouristDialog addDialog(user);
    addDialog.open();
    if(addDialog.exec() == QDialog::Accepted) {
        initTourists();
    }
}

void UserMainWindow::on_deleteButton_clicked()
{
    QTableView *touristsTableView = ui->mainWidget->widget(2)->findChild<QTableView *>("touristsTableView");

    // 未选中元素,不支持删除
    if(!touristsTableView->currentIndex().isValid()) {
        QMessageBox::warning(nullptr,"警告","当前未选中任何元素");
        qDebug() << "用户未选中行而执行删除" << Qt::endl;
        return;
    }

    QMessageBox::StandardButton res = QMessageBox::question(this, "删除确认", "您确定要删除吗?",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes) {
        qDebug() << "用户确认了删除操作" << Qt::endl;
        for(auto i : touristsTableView->selectionModel()->selectedIndexes()) {
            int row = i.row();

            // 企图删除自身对应的游客
            if(row == 0) {
                qDebug() << "用户试图删除自身对应的游客对象" << Qt::endl;
                res = QMessageBox::warning(nullptr, "警告", "代表用户自身的游客(表格第一项)不可删除");
            } else {
                Tourist tourist(touristsTableView->model()->index(row,0).data().toString(),touristsTableView->model()->index(row,1).data().toString(),touristsTableView->model()->index(row,2).data().toString());
                DatabaseTool::deleteTouristFromUser(user,tourist);
                qDebug() << "完成删除" << Qt::endl;
                initTourists();
            }
        }
    } else {
        qDebug() << "用户取消了删除操作" << Qt::endl;
    }
}
