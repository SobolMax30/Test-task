#include "logsender.h"

#include <QTimer>

LogSender::LogSender(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , client(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &LogSender::onNewConnection);

    QTimer *queueTimer = new QTimer(this);
    connect(queueTimer, &QTimer::timeout, this, &LogSender::processQueue);
    queueTimer->start(100);
}

LogSender::~LogSender()
{
    stopServer();
}

bool LogSender::startServer(quint16 port)
{
    return server->listen(QHostAddress::Any, port);
}

void LogSender::stopServer()
{
    if (client)
    {
        client->disconnectFromHost();
        client = nullptr;
    }
    server->close();
}

void LogSender::sendLog(const QString &message)
{
    queueMutex.lock();
    messageQueue.append(message);
    queueMutex.unlock();
}

void LogSender::onNewConnection()
{
    client = server->nextPendingConnection();
    connect(client, &QTcpSocket::disconnected, this, &LogSender::onClientDisconnected);
}

void LogSender::onClientDisconnected()
{
    client = nullptr;
}

void LogSender::processQueue()
{
    if (!client || client->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }

    queueMutex.lock();
    QStringList messages = messageQueue;
    messageQueue.clear();
    queueMutex.unlock();

    for (const QString &msg : messages)
    {
        client->write(msg.toUtf8());
        client->write("\n");
    }
    client->flush();
}
