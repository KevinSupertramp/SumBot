#include "ClientSession.h"

void ClientSession::HandleCharList(QString& packet)
{
    QStringList recvData = packet.mid(3).split("|");
    quint8 numChar = (quint8)recvData.at(1).toUShort();

    if (!numChar)
    {
        // No char, let's create it !
        // Ask random pseudo
        SendPacket(WorldPacket(MSG_CHAR_RANDOM_NAME));
    }
    else
    {
        // Sélectionner le premier perso
        WorldPacket data(MSG_CHAR_SELECT);
        data << recvData.at(2).split(";").at(0);
        SendPacket(data);
    }
}

// La fonction random n'est pas terrible ^^
void ClientSession::HandleCharRandomPseudo(QString& packet)
{
    QString name = packet.mid(3);

    WorldPacket data(CMSG_CHAR_CREATE);
    data << name;
    data << "|11|1|-1|-1|-1";
    SendPacket(data);

    // Vérifier si le personnage a bien été créé avec le paquet ?
    // [ Debug ] Send packet SMSG_CHAR_CREATE ( Header : AA| )
    // [ Debug ] Packet data : AA|
}

void ClientSession::HandleCharCreate(QString& /*packet*/)
{

}

void ClientSession::HandleCharSelect(QString& /*packet*/)
{
    // [ Debug ] Packet data : AS||2|Lusum|1|-1|1|111|4294967295|4294967295|4294967295|
    // [ Debug ] Received packet from <127.0.0.1> : Af

    SendPacket(WorldPacket(CMSG_GAME_CREATE));

    SendPacket(WorldPacket(CMSG_SERVER_DATE));
    SendPacket(WorldPacket(CMSG_GAME_INFORMATIONS));

    // Todo : make character moving randomly on map
}
