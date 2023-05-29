#include <QStandardItemModel>
#include <QMessageBox>

#include "selecttouristdialog.h"
#include "ui_selecttouristdialog.h"
#include "databasetool.h"

SelectTouristDialog::SelectTouristDialog(const QList<Tourist> &tourists, const Appointment &appointment, QWidget *parent) :
    QDialog(parent),
    appointment(appointment),
    tourists(tourists),
    ui(new Ui::SelectTouristDialog)
{
    ui->setupUi(this);

    delete ui->touristsTableView->model();

    // 初始化模型
    QStandardItemModel *touristsModel = new QStandardItemModel();
    touristsModel->setHorizontalHeaderLabels(QStringList() << "姓名" << "电话" << "身份证号");

    for(const auto &i : this->tourists) {
        touristsModel->appendRow(QList<QStandardItem *>() << new QStandardItem(i.getName()) << new QStandardItem(i.getPhone()) << new QStandardItem(i.getCardId()));
    }

    ui->touristsTableView->setModel(touristsModel);

    ui->touristsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = ui->touristsTableView->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    ui->touristsTableView->setSizePolicy(policy);
    ui->touristsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

SelectTouristDialog::~SelectTouristDialog()
{
    delete ui;
}

void SelectTouristDialog::on_cancleButton_clicked()
{
    reject();
}


void SelectTouristDialog::on_selectButton_clicked()
{
    // 未选中元素,不支持删除
    if(!ui->touristsTableView->selectionModel()->selectedIndexes().size()) {
        QMessageBox::warning(nullptr,"警告","当前未选中任何元素");
        qDebug() << "用户未选中行而执行选择" << Qt::endl;
        return;
    }

    QMessageBox::StandardButton res = QMessageBox::question(this, "预约确认", "您确定要为选中的这些用户预约吗?\n非代表用户自身的游客(即非表格第一项)在当前用户代预约后,不可查看与删除其预约信息,必须由本人才可操作",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes) {
        qDebug() << "用户确认了选择操作" << Qt::endl;

        if(appointment.getNumLimit() < appointment.getNum() + ui->touristsTableView->selectionModel()->selectedIndexes().size()) {
            QMessageBox::warning(nullptr,"不可预约","当前时间段剩余可预约人数不足,请预约其他时间或减少预约人数");
            return;
        }

        bool hasSelf = false;

        for(auto i : ui->touristsTableView->selectionModel()->selectedIndexes()) {
            int row = i.row();

            Tourist tourist(ui->touristsTableView->model()->index(row,0).data().toString(),ui->touristsTableView->model()->index(row,1).data().toString(),ui->touristsTableView->model()->index(row,2).data().toString());

            // 当前游客已预约
            if(DatabaseTool::isAppointed(tourist, appointment)) {
                QMessageBox::warning(nullptr,"不可预约","当前时间段游客" + tourist.getName() + "已预约,请勿重复预约");
                continue;
            }

            // 为自身对应的游客预约了
            if(row == 0) {
                qDebug() << "选中了用户本身对应的游客" << Qt::endl;
                hasSelf = true;
            }

            DatabaseTool::appoint(tourist, appointment);
            qDebug() << "游客"<< tourist.getName() <<"预约" << appointment.getDay().toString("yyyy/MM/dd") << "的从" << appointment.getStartTime().toString("mm:ss") << "到" << appointment.getEndTime().toString("mm:ss") << "的时间段" <<Qt::endl;
        }

        if(hasSelf) {
            accept();
        } else {
            reject();
        }
    } else {
        qDebug() << "用户取消了选择操作" << Qt::endl;
    }
}

