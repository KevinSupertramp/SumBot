#include "ClientSession.h"

void ClientSession::HandleAccountPseudo(QString& packet)
{
    m_pseudo = packet.right(2);
}
