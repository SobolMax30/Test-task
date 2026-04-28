#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include "logsender.h"
#include "icontainer.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QObject>
#include <QString>

template <class T>
class WriteThread : public QThread
{
public:
    WriteThread(int id,
                IContainer<T> *container,
                QMutex *mutex,
                QWaitCondition *cond,
                int n,
                int t1,
                int t2,
                bool *running,
                QElapsedTimer *globalTimer,
                LogSender *logSender,
                int *globalCounter,
                QObject *parent = nullptr)
        : QThread(parent)
        , id(id)
        , container(container)
        , mutex(mutex)
        , cond(cond)
        , n(n)
        , t1(t1)
        , t2(t2)
        , running(running)
        , globalTimer(globalTimer)
        , logSender(logSender)
        , globalCounter(globalCounter)
    {
    }

protected:
    void run() override
    {
        while (*running && globalTimer->elapsed() < t1 * 1000)
        {
            mutex->lock();

            *globalCounter = *globalCounter + 1;
            int currentValue = *globalCounter;

            for (int i = 0; i < n; ++i)
            {
                T item;
                item = currentValue;
                container->push(item);
            }

            int containerSize = static_cast<int>(container->size());
            std::vector<T> contents = container->getContents();
            QString contentsStr = "[";

            for (size_t j = 0; j < contents.size(); ++j)
            {
                if (j > 0)
                {
                    contentsStr += ", ";
                }
                int value = contents[j];
                contentsStr += QString::number(value);
            }
            contentsStr += "]";

            qint64 globalTime = globalTimer->elapsed();

            QString msg = QString("[ЗАПИСЬ] Поток %1\n"
                                  "  Добавлено элементов: %2\n"
                                  "  Размер контейнера после записи: %3\n"
                                  "  Общее время с начала процесса: %4 мс\n"
                                  "  Содержимое контейнера: %5")
                              .arg(id)
                              .arg(n)
                              .arg(containerSize)
                              .arg(globalTime)
                              .arg(contentsStr);

            logSender->sendLog(msg);

            mutex->unlock();
            cond->wakeAll();

            msleep(t2);
        }
    }

private:
    int id;
    IContainer<T> *container;
    QMutex *mutex;
    QWaitCondition *cond;
    int n;
    int t1;
    int t2;
    bool *running;
    QElapsedTimer *globalTimer;
    LogSender *logSender;
    int *globalCounter;
};

#endif // WRITETHREAD_H
