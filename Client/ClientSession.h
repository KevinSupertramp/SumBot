#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include "SocketHandler.h"

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

    virtual void ProcessPacket(QString packet);

    void HandleNULL(QString& /*packet*/) {}
    void HandleClientSide(QString& /*packet*/) {}

    // SMSG handlers
    void HandleAccountPseudo(QString& packet);
    void HandleHelloConnectionServer(QString& packet);
    void HandleRealmList(QString& packet);

    // MSG handlers
    void HandleQueuePosition(QString& packet);

public slots:
    virtual void OnClose();

private:
    QString m_hashKey;
    QString m_username;
    QString m_pseudo;

    sRealmInfos m_realmInfo;
};

#endif // CLIENTSESSION_H
