#include "commandreceiver.h"

CommandReceiver::CommandReceiver(QObject *parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    multicastAddress = QHostAddress("239.255.0.1");
    multicastPort = 45454;

    udpSocket->bind(QHostAddress::AnyIPv4, multicastPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(multicastAddress);

    connect(udpSocket, &QUdpSocket::readyRead, this, &CommandReceiver::onReadyRead);
}

CommandReceiver::~CommandReceiver()
{
    udpSocket->leaveMulticastGroup(multicastAddress);
    udpSocket->close();
}

void CommandReceiver::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        processDatagram(datagram);
    }
}

void CommandReceiver::processDatagram(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);

    if (message == "STOP")
    {
        emit stopReceived();
        return;
    }

    QStringList parts = message.split(';');

    if (parts.size() == 9 && parts[0] == "START")
    {
        QString containerType = parts[1];
        int N = parts[2].toInt();
        int M = parts[3].toInt();
        int NWrite = parts[4].toInt();
        int NRead = parts[5].toInt();
        int T1 = parts[6].toInt();
        int T2 = parts[7].toInt();
        QString dataType = parts[8];

        emit startReceived(containerType, N, M, NWrite, NRead, T1, T2, dataType);
    }
}
