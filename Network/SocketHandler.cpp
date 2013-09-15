#include "SocketHandler.h"

SocketHandler::SocketHandler()
{
    m_socket = NULL;
    m_packet = "";
}

void SocketHandler::OnRead()
{
    char *curChar = new char;
    while(m_socket->read(curChar, 1) > (qint64)0)
    {
        if(*curChar != 0x00)
        {
            if(*curChar != '\n' && *curChar != '\r')
                m_packet += *curChar;
        }
        else
        {
            ProcessPacket(m_packet);
            m_packet = "";
        }
    }
}

void SocketHandler::OnClose()
{
    qDebug() << "Closing connection with " << m_socket->peerAddress().toString();
    m_socket->deleteLater();
}

void SocketHandler::SendPacket(const WorldPacket& data) const
{
    m_socket->write(data.GetPacket().toLatin1() + (char)0x00);
    qDebug() << "Send packet " << GetOpcodeName(data.GetOpcode()) << " ( Header : " << GetOpcodeHeader(data.GetOpcode()) << " )";
    if(data.GetPacket().length() > 0)
        qDebug() << "Packet data : " << QString(data.GetPacket());
}
