#include "manager.h"
#include "pseudopicture.h"

#include <QDateTime>

Manager::Manager(QObject *parent)
    : QObject(parent)
    , running(false)
    , logSender(nullptr)
    , globalCounter(0)
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

void Manager::onStartReceived(const QString &containerType, int N, int M, int NWrite, int NRead, int T1, int T2, const QString &dataType)
{
    if (running)
    {
        onStopReceived();
    }

    running = true;
    timer.start();
    timeoutTimer->start(T1 * 1000);

    if (logSender)
    {
        logSender->sendLog("[СТАРТ] Процесс запущен в " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }

    if (dataType == "PseudoPicture")
    {
        startAlgorithm<PseudoPicture>(containerType, N, M, NWrite, NRead, T1, T2);
    }
    else
    {
        startAlgorithm<int>(containerType, N, M, NWrite, NRead, T1, T2);
    }
}

void Manager::onStopReceived()
{
    if (!running)
    {
        return;
    }

    if (logSender)
    {
        logSender->sendLog("[СТОП] Процесс остановлен в " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }

    stopAllThreads();
    globalCounter = 0;
}

void Manager::onTimeout()
{
    onStopReceived();
}

void Manager::stopAllThreads()
{
    running = false;
    cond.wakeAll();

    for (QThread *thread : threads)
    {
        thread->wait();
        delete thread;
    }
    threads.clear();

    timeoutTimer->stop();
}
