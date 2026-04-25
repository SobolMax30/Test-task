#include "logsender.h"

LogSender::LogSender(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , client(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &LogSender::onNewConnection);
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
    if (client && client->state() == QAbstractSocket::ConnectedState)
    {
        client->write(message.toUtf8());
        client->write("\n");
    }
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
