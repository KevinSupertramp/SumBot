#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetStarted(false);
    m_bots.clear();
    m_bot_number = 0;
    m_total_bot_number = 0;

    connect(ui->number_bot_valid, SIGNAL(clicked()), this, SLOT(ValidBotNumber()));
    connect(ui->confirm_start, SIGNAL(clicked()), this, SLOT(Start()));
}

MainWindow::~MainWindow()
{
    DeleteBots();

    delete ui;
}

void MainWindow::Log(QString line, bool newLine)
{
    if (newLine)
        ui->logs_view->appendPlainText(line);
    else
    {
        ui->logs_view->moveCursor(QTextCursor::End);
        ui->logs_view->insertPlainText(line);
        ui->logs_view->moveCursor(QTextCursor::End);
    }
}

void MainWindow::ValidBotNumber()
{
    m_total_bot_number = (quint8)ui->number_bot->value();
    ui->confirm_number_label->setText(QString::number(m_total_bot_number));

    ui->number_bot_valid->setDisabled(true);
}

void MainWindow::Start()
{
    if (IsStarted())
    {
        DeleteBots();

        ui->confirm_start->setText("Démarrer le test !");
        SetStarted(false);
    }
    else
    {
        if (!m_total_bot_number)
        {
            Log("Veuillez valider le nombre de bots à générer.");
            return;
        }

        Log("Démarrage des bots...");

        for (quint8 i = 0; i < m_total_bot_number; ++i)
        {
            Bot* bot = new Bot(i);
            bot->start();
            m_bots.insert(i, bot);

            connect(bot, SIGNAL(started()), this, SLOT(ThreadStarted()));
            connect(bot, SIGNAL(finished()), this, SLOT(ThreadStopped()));
            connect(bot, SIGNAL(LogSignal(QString)), this, SLOT(BotLog(QString)));
        }

        ui->confirm_start->setText("Stopper le test !");
        SetStarted(true);
    }
}

void MainWindow::ThreadStarted()
{
    ++m_bot_number;

    if (m_bot_number == m_total_bot_number)
        Log(QString::number(m_total_bot_number) + " bots démarré avec succès !");
}

void MainWindow::ThreadStopped()
{
    m_bot_number--;

    if (!m_bot_number)
        Log(QString::number(m_total_bot_number) + " bots stoppé avec succès !\n");
}

void MainWindow::DeleteBots()
{
    for (BotMap::ConstIterator bot = m_bots.begin(); bot != m_bots.end(); ++bot)
    {
        (*bot)->SetRunning(false);
        (*bot)->quit();
        (*bot)->wait();
        (*bot)->deleteLater();
    }
}
