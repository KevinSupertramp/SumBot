#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>

#include "bot.h"

namespace Ui {
class MainWindow;
}

typedef QMap<quint16, Bot*> BotMap;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetStarted(bool started) { m_started = started; }
    bool IsStarted() { return m_started; }

    void Log(QString line, bool newLine = true);

    void DeleteBots();

public slots:
    void ValidBotNumber();
    void Start();
    void ThreadStarted();
    void ThreadStopped();
    
private:
    Ui::MainWindow *ui;
    bool m_started;
    BotMap m_bots;
    quint8 m_bot_number;
    quint8 m_total_bot_number;
};

#endif // MAINWINDOW_H
