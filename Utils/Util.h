#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <ctime>
#include <QString>

void InitializeRand();
quint16 GenerateRandomNumber(quint16 max);
QString GenerateRandomString(quint8 length);
QString GenerateSessionKey();
QString Checksum(QString value);
QString HashPassword(QString password, QString hashKey);
QString GetCellString(quint16 cellId);


#endif
