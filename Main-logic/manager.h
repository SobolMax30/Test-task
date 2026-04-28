#ifndef MANAGER_H
#define MANAGER_H

#include "icontainer.h"
#include "container.h"
#include "writethread.h"
#include "readthread.h"
#include "logsender.h"

#include <deque>
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
    void onStartReceived(const QString &containerType, int N, int M, int NWrite, int NRead, int T1, int T2, const QString &dataType);
    void onStopReceived();
    void onTimeout();

private:
    QMutex mutex;
    QWaitCondition cond;
    bool running;
    QElapsedTimer timer;
    QTimer *timeoutTimer;
    LogSender *logSender;
    QVector<QThread*> threads;
    int globalCounter;

    void stopAllThreads();

    template <class T>
    IContainer<T>* createContainer(const QString &containerType)
    {
        if (containerType == "std::list")
        {
            return new Container<std::list<T>, T>();
        }
        else if (containerType == "std::deque")
        {
            return new Container<std::deque<T>, T>();
        }
        else
        {
            return new Container<std::vector<T>, T>();
        }
    }

    template <class T>
    void createAndStartWriters(IContainer<T> *container, int count, int N, int T1, int T2)
    {
        for (int i = 0; i < count; ++i)
        {
            WriteThread<T> *writer = new WriteThread<T>(i + 1, container, &mutex, &cond, N, T1, T2, &running, &timer, logSender, &globalCounter);
            threads.append(writer);
            writer->start();
        }
    }

    template <class T>
    void createAndStartReaders(IContainer<T> *container, int count, int M, int T1)
    {
        for (int i = 0; i < count; ++i)
        {
            ReadThread<T> *reader = new ReadThread<T>(i + 1, container, &mutex, &cond, M, T1, &running, &timer, logSender);
            threads.append(reader);
            reader->start();
        }
    }

    template <class T>
    void startAlgorithm(const QString &containerType, int N, int M, int NWrite, int NRead, int T1, int T2)
    {
        IContainer<T> *container = createContainer<T>(containerType);
        createAndStartWriters<T>(container, NWrite, N, T1, T2);
        createAndStartReaders<T>(container, NRead, M, T1);
    }
};

#endif // MANAGER_H
