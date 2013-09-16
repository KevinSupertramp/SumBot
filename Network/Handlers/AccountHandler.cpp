#include "ClientSession.h"
#include "Utils/Util.h"

void ClientSession::HandleAccountPseudo(QString& packet)
{
    m_pseudo = packet.mid(2);
}

void ClientSession::HandleAuthenticationResult(QString& packet)
{
    if (packet.mid(2, 1) == "E")
    {
        QString result = packet.mid(3);

        if (result == "f")
            Log("Erreur le compte sumbox_" + QString::number(GetBot()->GetId()) + " n'existe pas ou le mot de passe est incorrecte.");
    }
}

void ClientSession::HandleTicketResponse(QString& packet)
{
    if (packet.mid(2, 1) == "E")
    {
        Log("Erreur de connexion au serveur de jeu : clé de session invalide !");
        return;
    }


    // A placer ailleur théoriquement, à tester (j'essaie d'éviter d'envoyer tous les paquets)
    // [ Debug ] Received packet from <127.0.0.1> : AV
    // [ Debug ] Received packet from <127.0.0.1> : Agfr
    m_sessionKey = GenerateSessionKey();
    WorldPacket data(CMSG_SESSION_KEY);
    data << m_sessionKey;
    SendPacket(data);

    // Demander la liste des persos
    SendPacket(WorldPacket(CMSG_CHAR_LIST));

    // [ Debug ] Received packet from <127.0.0.1> : Af
}
