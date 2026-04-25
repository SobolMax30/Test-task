#ifndef COMMANDRECEIVER_H
#define COMMANDRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class CommandReceiver : public QObject
{
    Q_OBJECT
public:
    explicit CommandReceiver(QObject *parent = nullptr);
    ~CommandReceiver();

signals:
    void startReceived(const QString &containerType, int N, int M, int NWrite, int NRead, int T1, int T2);
    void stopReceived();

private slots:
    void onReadyRead();

private:
    QUdpSocket *udpSocket;
    QHostAddress multicastAddress;
    quint16 multicastPort;

    void processDatagram(const QByteArray &data);
};

#endif // COMMANDRECEIVER_H
