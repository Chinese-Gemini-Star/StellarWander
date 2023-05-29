#ifndef TOURIST_H
#define TOURIST_H

#include <QString>

class Tourist
{
    /**
     * @brief 游客名
     */
    QString name;

    /**
     * @brief 电话
     */
    QString phone;

    /**
     * @brief 身份证号
     */
    QString cardId;
public:
    Tourist();
    Tourist(QString name,QString phone,QString cardId);
    QString getName() const;
    QString getPhone() const;
    QString getCardId() const;
};

#endif // TOURIST_H
