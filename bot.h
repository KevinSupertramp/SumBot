#ifndef BOT_H
#define BOT_H

#include <QtCore>
#include <QThread>

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

    void run();

signals:
    void ThreadStarted(quint16 id, qint32 threadId);
    void ThreadStopped(quint16 id, qint32 threadId);
    
private:
    quint16 m_id;
    bool m_started;
    bool m_running;
};

#endif // BOT_H
