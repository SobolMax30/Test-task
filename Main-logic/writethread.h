#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include "icontainer.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

class WriteThread : public QThread
{
    Q_OBJECT
public:
    explicit WriteThread(int id,
                         IContainer *container,
                         QMutex *mutex,
                         QWaitCondition *cond,
                         int n,
                         int t1,
                         int t2,
                         bool *running,
                         QElapsedTimer *timer,
                         QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void logMessage(const QString &message);

private:
    int id;
    IContainer *container;
    QMutex *mutex;
    QWaitCondition *cond;
    int n;
    int t1;
    int t2;
    bool *running;
    QElapsedTimer *timer;
};

#endif // WRITETHREAD_H
