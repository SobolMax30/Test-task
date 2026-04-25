#ifndef MANAGER_H
#define MANAGER_H

#include "writethread.h"
#include "readthread.h"
#include "logsender.h"
#include "icontainer.h"

#include <memory>
#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QVector>
#include <QWaitCondition>
#include <QElapsedTimer>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
    ~Manager();

    void setLogSender(LogSender *logSender);

public slots:
    void onStartReceived(const QString &containerType,
                         int N, int M, int NWrite, int NRead, int T1, int T2);
    void onStopReceived();
    void onTimeout();

private:
    std::unique_ptr<IContainer> container;
    QMutex mutex;
    QWaitCondition cond;
    bool running;
    QElapsedTimer timer;
    QTimer *timeoutTimer;
    LogSender *logSender;
    QVector<WriteThread*> writers;
    QVector<ReadThread*> readers;

    void stopAllThreads();
};

#endif // MANAGER_H
