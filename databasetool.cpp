#include <QSqlQuery>
#include <QSqlError>
#include "databasetool.h"

DatabaseTool::DatabaseTool(){}

QString DatabaseTool::getPasswordByUserName(const QString &userName) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE userName=?");
    query.bindValue(0,userName);
    query.exec();
    QString password = "";
    if(query.next()) {
        qDebug() << "通过用户名找到指定用户" << Qt::endl;
        password = query.value(0).toString();
    } else {
        qDebug() << "未通过用户名找到指定用户" << Qt::endl;
    }
    return password;
}

QString DatabaseTool::getPasswordByPhone(const QString &phone) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE userName IN (SELECT userName FROM user_tourist_relations WHERE touristPhone = ? AND isSelf = 1)");
    query.bindValue(0,phone);
    query.exec();
    QString password = "";
    if(query.next()) {
        qDebug() << "通过手机号找到指定用户" << Qt::endl;
        password = query.value(0).toString();
    } else {
        qDebug() << "未通过手机号找到指定用户" << Qt::endl;
    }
    return password;
}

QString DatabaseTool::getUserNameByPhone(const QString &phone) {
    QSqlQuery query;
    query.prepare("SELECT userName FROM users WHERE userName IN (SELECT userName FROM user_tourist_relations WHERE touristPhone = ? AND isSelf = 1)");
    query.bindValue(0,phone);
    query.exec();
    QString userName = "";
    if(query.next()) {
        qDebug() << "通过手机号找到指定用户" << Qt::endl;
        userName = query.value(0).toString();
    } else {
        qDebug() << "未通过手机号找到指定用户" << Qt::endl;
    }
    return userName;
}

bool DatabaseTool::checkUserName(const User &user) {
    QSqlQuery query;
    query.prepare("SELECT userName FROM users WHERE userName=?");
    query.bindValue(0,user.getUserName());
    query.exec();
    if(query.next()) {
        return true;
    } else {
        return false;
    }
}

void DatabaseTool::setUser(const User &user) {
    QSqlQuery query;
    query.prepare("INSERT INTO users(userName, password) VALUES (?,?)");
    query.bindValue(0,user.getUserName());
    query.bindValue(1,user.getPassword());
    query.exec();
    qDebug() << "用户信息已加入数据库" << Qt::endl;
}

bool DatabaseTool::isTouristExist(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("SELECT name FROM tourists WHERE cardId=? AND phone=?");
    query.bindValue(0,tourist.getCardId());
    query.bindValue(1,tourist.getPhone());
    query.exec();
    if(query.next()) {
        return true;
    } else {
        return false;
    }
}

bool DatabaseTool::checkTouristName(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("SELECT name FROM tourists WHERE cardId=? AND phone=?");
    query.bindValue(0,tourist.getCardId());
    query.bindValue(1,tourist.getPhone());
    query.exec();
    if(query.next()) {
        if(query.value(0) != tourist.getName()) {
            return true;
        }
    }
    return false;
}

bool DatabaseTool::checkPhone(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("SELECT phone FROM tourists WHERE phone=?");
    query.bindValue(0,tourist.getPhone());
    query.exec();
    if(query.next()) {
        return true;
    } else {
        return false;
    }
}

bool DatabaseTool::checkId(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("SELECT cardId FROm tourists WHERE cardId=?");
    query.bindValue(0,tourist.getCardId());
    query.exec();
    if(query.next()) {
        return true;
    } else {
        return false;
    }
}

bool DatabaseTool::checkSelf(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("SELECT userName FROM user_tourist_relations WHERE isSelf=1 AND touristPhone=?");
    query.bindValue(0,tourist.getPhone());
    query.exec();
    if(query.next()) {
        return true;
    } else {
        return false;
    }
}

void DatabaseTool::setTourist(const Tourist &tourist) {
    QSqlQuery query;
    query.prepare("INSERT INTO tourists(name, phone, cardId) VALUES (?,?,?)");
    query.bindValue(0,tourist.getName());
    query.bindValue(1,tourist.getPhone());
    query.bindValue(2,tourist.getCardId());
    query.exec();
    qDebug() << "游客信息已加入数据库" << Qt::endl;
}

void DatabaseTool::linkTouristToUser(const User &user,const Tourist &tourist,bool isSelf) {
    QSqlQuery query;
    query.prepare("INSERT INTO user_tourist_relations(userName, touristPhone, isSelf) VALUES (?,?,?)");
    query.bindValue(0,user.getUserName());
    query.bindValue(1,tourist.getPhone());
    query.bindValue(2,(int)isSelf);
    query.exec();
    qDebug() << "用户" << user.getUserName() << "已与电话为" << tourist.getPhone() << "的游客绑定" << Qt::endl;
    if(isSelf) {
        qDebug() << "且为用户本人信息"<< Qt::endl;
    }
}

void DatabaseTool::setAppointment(const Appointment &appointment) {
    QSqlQuery query;
    query.prepare("INSERT INTO appointments(day, time_start, time_end, numLimit, num) VALUES (?,?,?,?,0)");
    query.bindValue(0,appointment.getDay().toString("yyyy/MM/dd"));
    query.bindValue(1,appointment.getStartTime().toString("hh:mm"));
    query.bindValue(2,appointment.getEndTime().toString("hh:mm"));
    query.bindValue(3,appointment.getNumLimit());
    query.exec();
    qDebug() << "位于" << appointment.getDay().toString("yyyy/MM/dd") << "的" << appointment.getStartTime().toString("hh:mm") << "至"
             << appointment.getEndTime().toString("hh:mm") << "人数上限为" << appointment.getNumLimit() << "的可预约时间已加入数据库";
}

bool DatabaseTool::checkAppointment(const Appointment &appointment) {
    QSqlQuery query;
    query.prepare("SELECT id FROM appointments WHERE day=? AND time_start=? AND time_end=?");
    query.bindValue(0,appointment.getDay().toString("yyyy/MM/dd"));
    query.bindValue(1,appointment.getStartTime().toString("hh:mm"));
    query.bindValue(2,appointment.getEndTime().toString("hh:mm"));
    query.exec();
    if(query.next()) {
        qDebug() << "尝试写入重复的可预约数据" << Qt::endl;
        return true;
    }
    return false;
}

void DatabaseTool::getTouristsByUser(const User &user, QList<Tourist> &tourists) {
    QSqlQuery query;

    tourists.clear();

    // 先找本体
    query.prepare("SELECT * FROM tourists WHERE phone IN (SELECT touristPhone FROM user_tourist_relations WHERE userName=? AND isSelf=1)");
    query.bindValue(0,user.getUserName());
    query.exec();
    query.next();
    tourists << Tourist(query.value("name").toString(),query.value("phone").toString(),query.value("cardId").toString());

    // 然后找其他人
    query.prepare("SELECT * FROM tourists WHERE phone IN (SELECT touristPhone FROM user_tourist_relations WHERE userName=? AND isSelf=0)");
    query.bindValue(0,user.getUserName());
    query.exec();
    while(query.next()) {
        tourists << Tourist(query.value("name").toString(),query.value("phone").toString(),query.value("cardId").toString());
    }

    qDebug() << "查找完毕,该用户共绑定" << tourists.size() << "个游客";
}

bool DatabaseTool::isRelated(const User &user,const Tourist &tourist) {
    QSqlQuery query;

    query.prepare("SELECT userName FROM user_tourist_relations WHERE touristPhone=? AND userName=?");
    query.bindValue(0,tourist.getPhone());
    query.bindValue(1,user.getUserName());
    query.exec();
    if(query.next()) {
        qDebug() << "当前游客已被当前用户绑定" << Qt::endl;
        return true;
    } else {
        return false;
    }
}

void DatabaseTool::deleteTouristFromUser(const User &user,const Tourist &tourist) {
    QSqlQuery query;

    query.prepare("DELETE FROM user_tourist_relations WHERE touristPhone=? AND isSelf=0");
    query.bindValue(0,tourist.getPhone());
    query.exec();
    if(query.next()) {
        qDebug() << "当前游客已与用户取消绑定" << Qt::endl;
    }
}

void DatabaseTool::appoint(const Tourist &tourist, const Appointment &appointment) {
    QSqlQuery query;

    query.prepare("UPDATE appointments SET num = num + 1 WHERE id=?");
    query.bindValue(0,appointment.getId());
    query.exec();
    qDebug() << "已更新已预约人数" << Qt::endl;

    query.prepare("INSERT INTO tourist_appointment_informations(touristId, appointmentId) VALUES (?,?)");
    query.bindValue(0,tourist.getCardId());
    query.bindValue(1,appointment.getId());
    query.exec();
    qDebug() << "已将该用户与该时间段绑定" << Qt::endl;
}

bool DatabaseTool::isAppointed(const Tourist &tourist, const Appointment &appointment) {
    QSqlQuery query;

    query.prepare("SELECT id FROM tourist_appointment_informations WHERE touristId=? AND appointmentId=?");
    query.bindValue(0,tourist.getCardId());
    query.bindValue(1,appointment.getId());
    query.exec();
    if(query.next()) {
        qDebug() << "当前时间段已被当前用户预约" << Qt::endl;
        return true;
    } else {
        return false;
    }
}

void DatabaseTool::disappoint(const Tourist &tourist,const Appointment &appointment) {
    QSqlQuery query;

    query.prepare("UPDATE appointments SET num = num - 1 WHERE id=?");
    query.bindValue(0,appointment.getId());
    query.exec();
    qDebug() << "已更新已预约人数" << Qt::endl;

    query.prepare("DELETE FROM tourist_appointment_informations WHERE touristId=? AND appointmentId=?");
    query.bindValue(0,tourist.getCardId());
    query.bindValue(1,appointment.getId());
    query.exec();
    qDebug() << "已将该用户与该时间段取消绑定" << Qt::endl;
}
