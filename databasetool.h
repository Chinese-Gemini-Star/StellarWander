#ifndef DATABASETOOL_H
#define DATABASETOOL_H

#include <QSqlDatabase>
#include <QDateTime>

#include "user.h"
#include "tourist.h"
#include "appointment.h"

/**
 * @brief 数据库操作工具类
 *
 * 提供各个静态方法,用于执行数据库相关的操作
 *
 * 本身不可实例化
 */
class DatabaseTool
{
    /**
     * @brief 不可实例化
     */
    DatabaseTool();
public:
    /**
     * @brief 从数据库中用用户名查找密码
     * @param 用户名
     * @return 密码
     */
    static QString getPasswordByUserName(const QString &userName);

    /**
     * @brief 从数据库中用电话查找密码
     * @param 电话
     * @return 密码
     */
    static QString getPasswordByPhone(const QString &phone);

    /**
     * @brief 确认用户名是否重复
     * @param 用户名
     * @return 是否重复
     */
    static bool checkUserName(const User &user);

    /**
     * @brief 将用户写入数据库
     * @param 用户对象
     */
    static void setUser(const User &user);

    /**
     * @brief 检查该用户是否已在数据库中
     * @param 用户对象
     * @return 是否已在数据库中
     */
    static bool isTouristExist(const Tourist &tourist);

    /**
     * @brief 确认电话是否重复
     * @param 游客对象
     * @return 是否重复
     */
    static bool checkPhone(const Tourist &tourist);

    /**
     * @brief 确认身份证是否重复
     * @param 游客对象
     * @return 是否重复
     */
    static bool checkId(const Tourist &tourist);

    /**
     * @brief 确认当前游客是否已有用户对象
     * @return 是否已有
     */
    static bool checkSelf(const Tourist &tourist);

    /**
     * @brief 当前用户是否已与当前游客绑定
     * @param 用户对象
     * @param 游客对象
     * @return 是否已绑定
     */
    static bool isRelated(const User &user,const Tourist &tourist);

    /**
     * @brief 将游客对象写入数据库
     * @param 游客对象
     */
    static void setTourist(const Tourist &tourist);

    /**
     * @brief 将游客对象绑定到用户对象上
     * @param 用户对象
     * @param 游客对象
     * @param 是否是本体
     */
    static void linkTouristToUser(const User &user,const Tourist &tourist,bool isSelf);

    /**
     * @brief 将游客对象从用户对象上取消绑定
     * @param 用户对象
     * @param 游客对象
     */
    static void deleteTouristFromUser(const User &user,const Tourist &tourist);

    /**
     * @brief 获取用户绑定的所有游客信息
     * @param 用户对象
     * @param 要存入的游客列表
     */
    static void getTouristsByUser(const User &user, QList<Tourist> &tourists);

    /**
     * @brief 将管理员新建的可预约时间加入数据库中
     * @param 可预约时间对象
     */
    static void setAppointment(const Appointment &appointment);

    /**
     * @brief 检查该可预约时间对象是否已在数据库中
     * @param 可预约时间对象
     * @return 是否已在数据库中
     */
    static bool checkAppointment(const Appointment &appointment);

    /**
     * @brief 预约一个时间
     * @param 游客对象
     * @param 可预约时间对象
     */
    static void appoint(const Tourist &tourist, const Appointment &appointment);

    /**
     * @brief 确认当前游客是否已预约此时间段
     * @param 游客对象
     * @param 可预约时间段
     */
    static bool isAppointed(const Tourist &tourist, const Appointment &appointment);

    /**
     * @brief 取消当前游客对当前时间段的预约
     * @param 游客对象
     * @param 可预约时间段
     */
    static void disappoint(const Tourist &tourist,const Appointment &appointment);
};
#endif // DATABASETOOL_H
