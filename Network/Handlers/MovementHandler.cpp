#include "ClientSession.h"

void ClientSession::HandleObjectMovement(QString& packet)
{
    if (!m_cellId)
        m_cellId = (quint16)packet.mid(3).split(";").at(0).toUShort();
}
