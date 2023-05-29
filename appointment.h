#ifndef APPOINEMENT_H
#define APPOINEMENT_H

#include <QDateTime>

class Appointment
{
    QDate day;
    QDateTime startTime, endTime;
    int numLimit;
    int id;
    int num;
public:
    Appointment(const QDate &day, const QDateTime &startTime, const QDateTime &endTime, int numLimit, int id = -1, int num = -1);
    QDate getDay() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    int getNumLimit() const;
    int getId() const;
    int getNum() const;
};

#endif // APPOINEMENT_H
