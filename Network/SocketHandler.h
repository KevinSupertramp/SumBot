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
    void OnRead();
    virtual void OnClose();

protected:
    QTcpSocket* m_socket;
    QString m_packet;
};

#endif // SOCKETREADER_H
