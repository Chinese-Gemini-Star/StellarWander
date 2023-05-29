#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class DetailDialog;
}

class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(int id, QWidget *parent = nullptr);
    ~DetailDialog();

private:
    Ui::DetailDialog *ui;
    QSqlTableModel tourists;

    /**
     * @brief 查找预约了指定时段的所有游客信息
     * @param 指定时段的id
     */
    void init(int id);
};

#endif // DETAILDIALOG_H
