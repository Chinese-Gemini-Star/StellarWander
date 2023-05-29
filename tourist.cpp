#include "tourist.h"

Tourist::Tourist(){}

Tourist::Tourist(QString name,QString phone,QString cardId) : name(name), phone(phone), cardId(cardId)
{
}

QString Tourist::getName() const {
    return name;
}
QString Tourist::getPhone() const{
    return phone;
}
QString Tourist::getCardId() const{
    return cardId;
}
