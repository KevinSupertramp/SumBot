#include "ClientSession.h"
#include "Utils/Util.h"

void ClientSession::HandleHelloConnectionServer(QString& packet)
{
    m_hashKey = packet.mid(2);

    WorldPacket data(CMSG_CLIENT_VERSION);
    data << "1.29.1";
    SendPacket(data);

    WorldPacket data2(CMSG_AUTHENTICATION);
    data2 << m_username;
    SendPacket(data2);

    WorldPacket data3(CMSG_AUTHENTICATION);
    data3 << "#1";
    data3 << HashPassword(m_username, m_hashKey);
    SendPacket(data3);

    SendPacket(WorldPacket(MSG_QUEUE_POSITION));
}

void ClientSession::HandleRealmList(QString& packet)
{
    QStringList recvData = packet.mid(2).split("|");
    QMap<quint8, sRealmInfos> realmsInfos;

    foreach (QString realmData, recvData)
    {
        QStringList realm = realmData.split(";");
        sRealmInfos realmInfos;

        realmInfos.realmId = (quint8)realm.at(0).toUShort();
        realmInfos.status = (quint8)realm.at(1).toUShort();
        realmInfos.completion = (quint8)realm.at(2).toUShort(); // completion ??
        realmInfos.canLogin = (quint8)realm.at(3).toUShort();

        realmsInfos[realmInfos.realmId] = realmInfos;
    }

    // Choix de l'ID du royaume dans fichier de config' ?
    WorldPacket data(CMSG_REALM_INFOS);
    data << realmsInfos.lowerBound(0).value().realmId;
    SendPacket(data);
}

void ClientSession::HandleRealmInfos(QString& packet)
{
    QStringList recvData = packet.mid(3).split(";");
    QStringList server = recvData.at(0).split(":");

    QHostAddress address = QHostAddress(server.at(0));
    quint16 port = (quint16)server.at(1).toUShort();
    m_ticketKey = recvData.at(1);

    ConnectToWorldServer(address, port);
}

void ClientSession::HandleHelloGameServer(QString& /*packet*/)
{
    WorldPacket data(MSG_TICKET);
    data << m_ticketKey;
    SendPacket(data);
}
