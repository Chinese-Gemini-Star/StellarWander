#ifndef USER_H
#define USER_H

#include <QString>

/**
 * @brief 用户
 *
 * 包含用户相关的属性以及操作
 */
class User
{
    /**
     * @brief 用户名
     */
    QString userName;
    /**
     * @brief 密码
     */
    QString password;
public:
    User();
    User(QString userName,QString password);
    QString getUserName() const;
    QString getPassword() const;
};

#endif // USER_H
