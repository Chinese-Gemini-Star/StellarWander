#include "adminmainwindow.h"
#include "usermainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 打开数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("StellarWanderDatabase.db");
    db.open();

    // 自动生成的不知道干嘛用的翻译器
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "StellarWander_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // 初始化登录界面
    LoginDialog login;
    login.show();
    if(login.exec() == QDialog::Accepted) {
        qDebug() << "账号验证通过" << Qt::endl;
        User user = login.getUser(); // 当前登录的用户对象
        if(user.getUserName() == "root") {
            qDebug() << "管理员登录" << Qt::endl;
            AdminMainWindow adminWindow;
            adminWindow.show();
            a.exec();
        } else {
            qDebug() << "用户登录" << Qt::endl;
            UserMainWindow userWindow(user);
            userWindow.show();
            a.exec();
        }
    }
    db.close();
    return 0;
}
