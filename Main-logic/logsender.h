#ifndef LOGSENDER_H
#define LOGSENDER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

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

private:
    QTcpServer *server;
    QTcpSocket *client;
};

#endif // LOGSENDER_H
