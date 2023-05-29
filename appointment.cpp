#include "appointment.h"

Appointment::Appointment(const QDate &day, const QDateTime &startTime, const QDateTime &endTime, int numLimit, int id, int num)
    :day(day), startTime(startTime), endTime(endTime) ,numLimit(numLimit), id(id), num(num){}

QDate Appointment::getDay() const{
    return day;
}

QDateTime Appointment::getStartTime() const{
    return startTime;
}

QDateTime Appointment::getEndTime() const{
    return endTime;
}

int Appointment::getNumLimit() const{
    return numLimit;
}

int Appointment::getId() const{
    return id;
}

int Appointment::getNum() const{
    return num;
}
