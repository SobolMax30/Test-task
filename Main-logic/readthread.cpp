#include "readthread.h"
#include "pseudopicture.h"

ReadThread::ReadThread(int id,
                       IContainer *container,
                       QMutex *mutex,
                       QWaitCondition *cond,
                       int m,
                       int t1,
                       bool *running,
                       QElapsedTimer *timer,
                       QObject *parent)
    : QThread(parent)
    , id(id)
    , container(container)
    , mutex(mutex)
    , cond(cond)
    , m(m)
    , t1(t1)
    , running(running)
    , timer(timer)
{
}

void ReadThread::run()
{
    while (*running && timer->elapsed() < t1 * 1000)
    {
        mutex->lock();

        while (*running && timer->elapsed() < t1 * 1000 && container->size() < static_cast<std::size_t>(m))
        {
            cond->wait(mutex);
        }

        if (!(*running) || timer->elapsed() >= t1 * 1000)
        {
            mutex->unlock();
            break;
        }

        int elementsRead = 0;
        for (int i = 0; i < m && !container->empty(); i++)
        {
            container->pop();
            elementsRead++;
        }

        int containerSize = container->size();
        mutex->unlock();

        qint64 elapsed = timer->elapsed();
        QString logText = QString("[ЧТЕНИЕ] Поток %1 | Извлечено элементов: %2 | Размер контейнера: %3 | Время: %4 мс")
                              .arg(id)
                              .arg(elementsRead)
                              .arg(containerSize)
                              .arg(elapsed);

        emit logMessage(logText);
    }
}
