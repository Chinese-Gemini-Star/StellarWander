#include "selectappointmentrule.h"

SelectAppointmentRule::SelectAppointmentRule(QDate startDay, QDate endDay, QDateTime startTime, QDateTime endTime, int numLimitS, int numLimitE, int numS, int numE)
    :startDay(startDay), endDay(endDay), startTime(startTime), endTime(endTime), numLimitS(numLimitS), numLimitE(numLimitE),numS(numS), numE(numE) {}

void SelectAppointmentRule::setStartDay(QDate &startDay) {
    this->startDay = startDay;
}

QDate &SelectAppointmentRule::getStartDay() {
    return startDay;
}

void SelectAppointmentRule::setEndDay(QDate &endDay) {
    this->endDay = endDay;
}

QDate &SelectAppointmentRule::getEndDay() {
    return endDay;
}

void SelectAppointmentRule::setStartTime(QDateTime &startTime) {
    this->startTime = startTime;
}

QDateTime &SelectAppointmentRule::getStartTime() {
    return startTime;
}

void SelectAppointmentRule::setEndTime(QDateTime &endTime) {
    this->endTime = endTime;
}

QDateTime &SelectAppointmentRule::getEndTime() {
    return endTime;
}

void SelectAppointmentRule::setNumLimitS(int numLimitS) {
    this->numLimitS = numLimitS;
}

int SelectAppointmentRule::getNumLimitS() {
    return numLimitS;
}

void SelectAppointmentRule::setNumLimitE(int numLimitE) {
    this->numLimitE = numLimitE;
}

int SelectAppointmentRule::getNumLimitE() {
    return numLimitE;
}

void SelectAppointmentRule::setNumS(int numS) {
    this->numS = numS;
}

int SelectAppointmentRule::getNumS() {
    return numS;
}

void SelectAppointmentRule::setNumE(int numE) {
    this->numE = numE;
}

int SelectAppointmentRule::getNumE() {
    return numE;
}
