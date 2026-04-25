#include "manager.h"
#include "container.h"

#include <QDateTime>
#include <vector>
#include <list>
#include <deque>

Manager::Manager(QObject *parent)
    : QObject(parent)
    , running(false)
    , logSender(nullptr)
{
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Manager::onTimeout);
}

Manager::~Manager()
{
    stopAllThreads();
}

void Manager::setLogSender(LogSender *sender)
{
    logSender = sender;
}

void Manager::onStartReceived(const QString &containerType, int N, int M, int NWrite, int NRead, int T1, int T2)
{
    if (running) onStopReceived();

    if (containerType == "std::vector")
    {
        container = std::make_unique<Container<std::vector<PseudoPicture>>>();
    }
    else if (containerType == "std::list")
    {
        container = std::make_unique<Container<std::list<PseudoPicture>>>();
    }
    else
    {
        container = std::make_unique<Container<std::deque<PseudoPicture>>>();
    }

    running = true;
    timer.start();
    timeoutTimer->start(T1 * 1000);

    if (logSender)
    {
        logSender->sendLog("[СТАРТ] Процесс запущен в " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }

    for (int i = 0; i < NWrite; i++)
    {
        WriteThread *writer = new WriteThread(i + 1, container.get(), &mutex, &cond, N, T1, T2, &running, &timer);
        connect(writer, &WriteThread::logMessage, logSender, &LogSender::sendLog);
        writers.append(writer);
        writer->start();
    }

    for (int i = 0; i < NRead; i++)
    {
        ReadThread *reader = new ReadThread(i + 1, container.get(), &mutex, &cond, M, T1, &running, &timer);
        connect(reader, &ReadThread::logMessage, logSender, &LogSender::sendLog);
        readers.append(reader);
        reader->start();
    }
}

void Manager::onStopReceived()
{
    if (!running) return;

    if (logSender)
    {
        logSender->sendLog("[СТОП] Процесс остановлен в " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }

    stopAllThreads();
}

void Manager::onTimeout()
{
    onStopReceived();
}

void Manager::stopAllThreads()
{
    running = false;
    cond.wakeAll();

    for (WriteThread *writer : writers)
    {
        writer->wait();
        delete writer;
    }
    writers.clear();

    for (ReadThread *reader : readers)
    {
        reader->wait();
        delete reader;
    }
    readers.clear();

    timeoutTimer->stop();
}
