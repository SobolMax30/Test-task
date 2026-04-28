#ifndef LOGSENDER_H
#define LOGSENDER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QStringList>

class LogSender : public QObject
{
    Q_OBJECT
public:
    explicit LogSender(QObject *parent = nullptr);
    ~LogSender();

    bool startServer(quint16 port);
    void stopServer();

    void sendLog(const QString &message);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void processQueue();

private:
    QTcpServer *server;
    QTcpSocket *client;
    QMutex queueMutex;
    QStringList messageQueue;
};

#endif // LOGSENDER_H
