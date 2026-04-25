#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    logModel = new QStringListModel(this);
    ui->logListView->setModel(logModel);

    ui->btnDisconnect->setEnabled(false);

    connect(tcpSocket, &QTcpSocket::connected, this, &MainWindow::onSocketConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &MainWindow::onSocketDisconnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::onSocketReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    tcpSocket->connectToHost("127.0.0.1", 12345);
}

void MainWindow::on_btnDisconnect_clicked()
{
    tcpSocket->disconnectFromHost();
}

void MainWindow::on_btnClear_clicked()
{
    logLines.clear();
    logModel->setStringList(logLines);
}

void MainWindow::onSocketConnected()
{
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    addLogLine("Подключено к серверу");
}

void MainWindow::onSocketDisconnected()
{
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    addLogLine("Отключено от сервера");
}

void MainWindow::onSocketReadyRead()
{
    while (tcpSocket->canReadLine())
    {
        QString receivedLine = QString::fromUtf8(tcpSocket->readLine()).trimmed();
        if (!receivedLine.isEmpty())
        {
            addLogLine(receivedLine);
        }
    }
}

void MainWindow::addLogLine(QString text)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    logLines.append("[" + timestamp + "] " + text);
    logModel->setStringList(logLines);
}
