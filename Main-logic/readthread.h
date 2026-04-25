#ifndef READTHREAD_H
#define READTHREAD_H

#include "icontainer.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(int id,
                        IContainer *container,
                        QMutex *mutex,
                        QWaitCondition *cond,
                        int m,
                        int t1,
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
    int m;
    int t1;
    bool *running;
    QElapsedTimer *timer;
};

#endif // READTHREAD_H
