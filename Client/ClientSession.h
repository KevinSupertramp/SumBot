#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include "SocketHandler.h"
#include "bot.h"

class Bot;

struct sRealmInfos
{
    quint8 realmId, status, completion;
    bool canLogin;
};

class ClientSession : public SocketHandler
{
    Q_OBJECT
public:
    ClientSession(quint8 botId);
    ~ClientSession();

    void SetBot(Bot* bot) { m_bot = bot; }
    Bot* GetBot() const { return m_bot; }
    void Log(QString line);

    void ConnectToWorldServer(QHostAddress address, quint16 port);
    virtual void ProcessPacket(QString packet);

    void HandleNULL(QString& /*packet*/) {}
    void HandleClientSide(QString& /*packet*/) {}

    // SMSG handlers
    void HandleAccountPseudo(QString& packet);
    void HandleAuthenticationResult(QString& packet);
    void HandleCharCreate(QString& packet);
    void HandleCharList(QString& packet);
    void HandleHelloConnectionServer(QString& packet);
    void HandleHelloGameServer(QString& packet);
    void HandleRealmInfos(QString& packet);
    void HandleRealmList(QString& packet);

    // MSG handlers
    void HandleCharRandomPseudo(QString& packet);
    void HandleCharSelect(QString& packet);
    void HandleQueuePosition(QString& packet);
    void HandleTicketResponse(QString& packet);

public slots:
    virtual void OnClose();
    virtual void OnError(QAbstractSocket::SocketError error);

private:
    Bot* m_bot;
    QString m_hashKey;
    QString m_username;
    QString m_pseudo;

    sRealmInfos m_realmInfo;
    QString m_ticketKey;
    QString m_sessionKey;
    bool m_connectedToWorld;
};

#endif // CLIENTSESSION_H
