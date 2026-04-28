#ifndef READTHREAD_H
#define READTHREAD_H

#include "logsender.h"
#include "icontainer.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QObject>
#include <QString>

template <class T>
class ReadThread : public QThread
{
public:
    ReadThread(int id,
               IContainer<T> *container,
               QMutex *mutex,
               QWaitCondition *cond,
               int m,
               int t1,
               bool *running,
               QElapsedTimer *globalTimer,
               LogSender *logSender,
               QObject *parent = nullptr)
        : QThread(parent)
        , id(id)
        , container(container)
        , mutex(mutex)
        , cond(cond)
        , m(m)
        , t1(t1)
        , running(running)
        , globalTimer(globalTimer)
        , logSender(logSender)
    {
    }

protected:
    void run() override
    {
        while (*running && globalTimer->elapsed() < t1 * 1000)
        {
            mutex->lock();

            while (container->size() < static_cast<std::size_t>(m))
            {
                cond->wait(mutex);
                if (!(*running) || globalTimer->elapsed() >= t1 * 1000)
                {
                    mutex->unlock();
                    return;
                }
            }

            int elementsRead = 0;
            for (int i = 0; i < m && !container->empty(); ++i)
            {
                container->pop();
                ++elementsRead;
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

            QString msg = QString("[ЧТЕНИЕ] Поток %1\n"
                                  "  Извлечено элементов: %2\n"
                                  "  Размер контейнера после извлечения: %3\n"
                                  "  Общее время с начала процесса: %4 мс\n"
                                  "  Содержимое контейнера: %5")
                              .arg(id)
                              .arg(elementsRead)
                              .arg(containerSize)
                              .arg(globalTime)
                              .arg(contentsStr);

            logSender->sendLog(msg);

            mutex->unlock();
            msleep(1);
        }
    }

private:
    int id;
    IContainer<T> *container;
    QMutex *mutex;
    QWaitCondition *cond;
    int m;
    int t1;
    bool *running;
    QElapsedTimer *globalTimer;
    LogSender *logSender;
};

#endif // READTHREAD_H
