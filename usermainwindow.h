#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "user.h"
#include "tourist.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(const User &user, QWidget *parent = nullptr);
    ~UserMainWindow();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void update();

private:
    Ui::UserMainWindow *ui;
    User user;
    QList<Tourist> tourists;
    void initTourists();
    void initAppointmentAvailable();
    void initAppointmentReserved();

};

#endif // USERMAINWINDOW_H
