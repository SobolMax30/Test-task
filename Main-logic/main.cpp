#include "manager.h"
#include "logsender.h"
#include "commandreceiver.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    CommandReceiver receiver;
    Manager manager;
    LogSender logSender;

    logSender.startServer(12345);
    manager.setLogSender(&logSender);

    QObject::connect(&receiver, &CommandReceiver::startReceived, &manager, &Manager::onStartReceived);
    QObject::connect(&receiver, &CommandReceiver::stopReceived, &manager, &Manager::onStopReceived);

    return application.exec();
}
