#ifndef BOT_H
#define BOT_H

#include <QtCore>
#include <QThread>
#include "ClientSession.h"

class Bot : public QThread
{
    Q_OBJECT
public:
    Bot(quint16 id);
    ~Bot();

    quint16 GetId() const { return m_id; }

    void SetStarted(bool started) { m_started = started; }
    bool IsStarted() { return m_started; }

    void SetRunning(bool running) { m_running = running; }
    bool IsRunning() { return m_running; }

    void Log(QString line) { emit LogSignal(QString("[Bot " + QString::number(GetId()) + "] : ") + line); }
    void run();

signals:
    void ThreadStarted(quint16 id, qint32 threadId);
    void ThreadStopped(quint16 id, qint32 threadId);
    void LogSignal(QString line);
    
private:
    quint16 m_id;
    bool m_started;
    bool m_running;

    ClientSession* m_session;
};

#endif // BOT_H
