#include "Util.h"
#include <QRegExp>
#include <QList>
#include <QtCore>
#include <QCryptographicHash>

QString charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
QString hexChar = "0123456789ABCDEF";

void InitializeRand()
{
    srand(time(NULL));
}

quint16 GenerateRandomNumber(quint16 max)
{
    InitializeRand();
    return rand() % max;
}

QString GenerateRandomString(quint8 length)
{
    InitializeRand();

    QString result;
    for(quint8 i = 0; i < length; ++i)
        result[i] = charset[rand() % charset.length()];

    return result;
}

// Pas vraiment le même algo que le client.
QString GenerateSessionKey()
{
    quint8 keyLength = (quint8)(GenerateRandomNumber(20) + 10);
    QString key = GenerateRandomString(keyLength);
    return Checksum(key);
}

QString Checksum(QString value)
{
    return QString(QCryptographicHash::hash(value.toLatin1(), QCryptographicHash::Md5).toHex());
}

QString HashPassword(QString password, QString hashKey)
{
    QString hashPassword = "";

    for (int i = 0; i < password.length(); i++)
    {
        char PPass = password[i].toLatin1();
        char PKey = hashKey[i].toLatin1();

        int APass = (int)PPass / 16;
        int AKey = (int)PPass % 16;

        int ANB = (APass + (int)PKey) % charset.length();
        int ANB2 = (AKey + (int)PKey) % charset.length();

        hashPassword += charset[ANB];
        hashPassword += charset[ANB2];
    }

    return hashPassword;
}
