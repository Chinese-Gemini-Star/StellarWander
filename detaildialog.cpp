#include "detaildialog.h"
#include "ui_detaildialog.h"

DetailDialog::DetailDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);

    ui->touristTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSizePolicy policy = ui->touristTableView->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    ui->touristTableView->setSizePolicy(policy);
    ui->touristTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    init(id);
}

void DetailDialog::init(int id) {
    // 打开数据表
    tourists.setTable("tourists");

    QString where = QString("cardId IN (SELECT touristId FROM tourist_appointment_informations WHERE appointmentId = %1)")
                       .arg(id);
    tourists.setFilter(where);
    tourists.select();
    qDebug() << "执行了查询" << where << Qt::endl;

    // 设置各列标题
    tourists.setHeaderData(0, Qt::Horizontal, "姓名");
    tourists.setHeaderData(1, Qt::Horizontal, "电话");
    tourists.setHeaderData(2, Qt::Horizontal, "身份证号");

    ui->touristTableView->setModel(&tourists);
}

DetailDialog::~DetailDialog()
{
    delete ui;
}
