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
    /*while (IsRunning())
    {
        if (!IsStarted())
        {
            SetStarted(true);
            emit ThreadStarted(m_id, (qint32)thread()->currentThreadId());
        }
    }

    SetStarted(false);
    emit ThreadStopped(m_id, (qint32)thread()->currentThreadId());
    */

    m_session = new ClientSession(m_id);

    exec();

    m_session->OnClose();
    delete m_session;
}
