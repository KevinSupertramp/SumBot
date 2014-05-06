#include "bot.h"

Bot::Bot(quint16 id)
{
    m_id = id;
    SetStarted(false);
    SetRunning(true);
    m_session = NULL;

    setParent(0);
    moveToThread(this);
}

Bot::~Bot()
{
}

void Bot::run()
{
    m_session = new ClientSession(m_id);
    m_session->SetBot(this);

    exec();

    m_session->OnClose();
    delete m_session;
}
