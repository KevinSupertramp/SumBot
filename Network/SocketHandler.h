#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtNetwork>
#include <QTcpSocket>
#include "Packets/WorldPacket.h"
#include "Opcodes/Opcodes.h"

class WorldPacket;

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    SocketHandler();

    void SendPacket(const WorldPacket& data) const;
    virtual void ProcessPacket(QString packet) = 0;

public slots:
    void OnConnect();
    void OnRead();
    void OnDisconnect();
    virtual void OnClose();
    virtual void OnError(QAbstractSocket::SocketError error) = 0;

protected:
    QTcpSocket* m_socket;
    QString m_packet;
};

#endif // SOCKETREADER_H
