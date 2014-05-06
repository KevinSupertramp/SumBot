#include "ClientSession.h"
#include "bot.h"
#include "Opcodes/Opcodes.h"
#include "Utils/Util.h"

ClientSession::ClientSession(quint8 botId) : SocketHandler()
{
    m_bot = NULL;
    m_hashKey = QString();
    m_username = "sumbot" + QString::number(botId);
    m_pseudo = QString();
    m_ticketKey = QString();
    m_sessionKey = QString();
    m_connectedToWorld = false;

    m_cellId = 0;

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::LocalHost, (quint16)50885);

    connect(m_socket, SIGNAL(connected()), this, SLOT(OnConnect()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnect()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError(QAbstractSocket::SocketError)));
}

ClientSession::~ClientSession()
{
}

void ClientSession::Log(QString line)
{
    if (m_bot)
        m_bot->Log(line);
}

void ClientSession::ConnectToWorldServer(QHostAddress address, quint16 port)
{
    m_socket->abort();
    m_socket->connectToHost(address, port);
    m_connectedToWorld = true;

    qDebug() << "Connect to host " << address << " on port " << port;
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

void ClientSession::RandomMove()
{
    if ((m_cellId % 3) == 0)
        m_cellId += 3;
    else
        m_cellId -= 3;

    WorldPacket data(MSG_GAME_ACTION);
    data << "001"; // Moving
    data << "h" << GetCellString(m_cellId);
    SendPacket(data);

    qDebug() << "Send RandomMove packet : " << data.GetPacket();

    QEventLoop loop;
    QTimer timer;

    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(2000); // wait 2sec
    loop.exec();

    // Lazyyyyy
    WorldPacket data2(MSG_UNKNOWN_OPCODE);
    data2 << "GKK0";
    SendPacket(data2);
    qDebug() << "Packet GKK sended";
}

void ClientSession::OnClose()
{
    SocketHandler::OnClose();
}

void ClientSession::OnError(QAbstractSocket::SocketError /*error*/)
{
    if (m_connectedToWorld)
        Log("Impossible de se connecter au serveur de jeu.");
    else
        Log("Impossible de se connecter au serveur d'authentification.");
}
