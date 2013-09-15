#include "ClientSession.h"
#include "Opcodes/Opcodes.h"

ClientSession::ClientSession(quint8 botId) : SocketHandler()
{
    m_hashKey = QString();
    m_username = "sumbot_" + QString::number(botId);

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::LocalHost, 50885);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

ClientSession::~ClientSession()
{
}

void ClientSession::ProcessPacket(QString packet)
{
    if(packet.isEmpty())
        return;

    qDebug() << "Received packet from : " << packet;

    QString header2 = packet.left(2);
    QString header3 = packet.left(3);

    OpcodeStruct opcode = GetOpcodeByHeader(header3);

    if (opcode.name == "MSG_UNKNOWN_OPCODE")
        opcode = GetOpcodeByHeader(header2);

    if (opcode.name != "MSG_UNKNOWN_OPCODE")
        (this->*opcode.handler)(packet);
    else
        qDebug() << "Packet <" << header2 << "> is unhandled. Content : " << packet;
}

void ClientSession::OnClose()
{
    SocketHandler::OnClose();
}
