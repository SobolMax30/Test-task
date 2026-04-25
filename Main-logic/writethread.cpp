#include "writethread.h"
#include "pseudopicture.h"

WriteThread::WriteThread(int id,
                         IContainer *container,
                         QMutex *mutex,
                         QWaitCondition *cond,
                         int n,
                         int t1,
                         int t2,
                         bool *running,
                         QElapsedTimer *timer,
                         QObject *parent)
    : QThread(parent)
    , id(id)
    , container(container)
    , mutex(mutex)
    , cond(cond)
    , n(n)
    , t1(t1)
    , t2(t2)
    , running(running)
    , timer(timer)
{
}

void WriteThread::run()
{
    while (*running && timer->elapsed() < t1 * 1000)
    {
        mutex->lock();

        for (int i = 0; i < n; i++)
        {
            PseudoPicture picture;
            picture.fillRandom();
            container->push(picture);
        }

        int containerSize = container->size();
        mutex->unlock();

        cond->wakeAll();

        qint64 elapsed = timer->elapsed();
        QString logText = QString("[ЗАПИСЬ] Поток %1 | Добавлено элементов: %2 | Размер контейнера: %3 | Время: %4 мс")
                              .arg(id)
                              .arg(n)
                              .arg(containerSize)
                              .arg(elapsed);

        emit logMessage(logText);

        msleep(t2);
    }
}
