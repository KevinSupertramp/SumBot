#include "ClientSession.h"

QString HashPassword(QString password, QString hashKey)
{
    QString charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
    QString passwordHash = "";

    for (int i = 0; i < password.length(); i++)
    {
        char PPass = password[i].toLatin1();
        char PKey = hashKey[i].toLatin1();

        int APass = (int)PPass / 16;
        int AKey = (int)PPass % 16;

        int ANB = (APass + (int)PKey) % charset.length();
        int ANB2 = (AKey + (int)PKey) % charset.length();

        passwordHash += charset[ANB];
        passwordHash += charset[ANB2];
    }

    return passwordHash;
}

void ClientSession::HandleHelloConnectionServer(QString& packet)
{
    m_hashKey = packet.right(2);

    WorldPacket data(CMSG_CLIENT_VERSION);
    data << "1.29.1";
    SendPacket(data);

    WorldPacket data2(CMSG_AUTHENTICATION);
    data2 << m_username;
    data2 << "#1";
    data2 << HashPassword(m_username, m_hashKey);
    SendPacket(data2);

    SendPacket(WorldPacket(MSG_QUEUE_POSITION));
}

void ClientSession::HandleRealmList(QString& packet)
{
    QString realmList = packet.right(2);
    QStringList realmInfos = QStringList();

    if (realmList.contains("|"))
        realmInfos = realmList.split("|").at(0).split(";");
    else
        realmInfos = realmList.split(";");

    sRealmInfos realmInfo;
    realmInfo.realmId = (quint8)realmInfos.at(0).toUShort();
    realmInfo.status = (quint8)realmInfos.at(1).toUShort();
    realmInfo.completion = (quint8)realmInfos.at(2).toUShort(); // completion ??
    realmInfo.canLogin = realmInfos.at(3).toUShort() == 1;

    m_realmInfo = realmInfo;
}
