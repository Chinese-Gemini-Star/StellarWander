#ifndef SELECTAPPOINTMENTRULE_H
#define SELECTAPPOINTMENTRULE_H

#include <QDateTime>

class SelectAppointmentRule
{
    QDate startDay;
    QDate endDay;
    QDateTime startTime;
    QDateTime endTime;
    int numLimitS,numLimitE;
    int numS,numE;
public:
    SelectAppointmentRule(QDate startDay = QDate::currentDate(), QDate endDay = QDate::currentDate(), QDateTime startTime = QDateTime::fromString("00:00", "hh:mm"), QDateTime endTime = QDateTime::fromString("23:59", "hh:mm"), int numLimitS = -1, int numLimitE = -1, int numS = -1, int numE = -1);
    void setStartDay(QDate &startDay);
    QDate &getStartDay();
    void setEndDay(QDate &endDay);
    QDate &getEndDay();
    void setStartTime(QDateTime &startTime);
    QDateTime &getStartTime();
    void setEndTime(QDateTime &endTime);
    QDateTime &getEndTime();
    void setNumLimitS(int numLimitS);
    int getNumLimitS();
    void setNumLimitE(int numLimitE);
    int getNumLimitE();
    void setNumS(int numS);
    int getNumS();
    void setNumE(int numE);
    int getNumE();
};

#endif // SELECTAPPOINTMENTRULE_H
