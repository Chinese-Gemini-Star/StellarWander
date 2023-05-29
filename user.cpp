#include "user.h"

User::User(): userName(""), password(""){}

User::User(QString userName,QString password): userName(userName), password(password) {

}

QString User::getUserName() const {
    return userName;
}

QString User::getPassword() const {
    return password;
}
