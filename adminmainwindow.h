#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QString>

#include "selectappointmentrule.h"

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private slots:
    void on_newAction_triggered();

    void on_deleteAction_triggered();

    void on_todayAction_triggered();

    void on_threeAction_triggered();

    void on_weekAction_triggered();

    void on_monthAction_triggered();

    void on_selectAction_triggered();

    void on_detailAction_triggered();

private:
    Ui::AdminMainWindow *ui;
    QSqlTableModel appointmentInfo;
    SelectAppointmentRule prevWhere;
    /**
     * @brief 绑定数据至视图
     */
    void bindData();

    /**
     * @brief 以指定规则查找数据
     * @param 查找规则
     */
    void selectDate(const SelectAppointmentRule where);

    /**
     * @brief 以上一次的规则查找数据(即刷新)
     */
    void selectDate();
};

#endif // ADMINMAINWINDOW_H
