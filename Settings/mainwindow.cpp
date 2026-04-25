#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , udpSocket(new QUdpSocket(this))
    , settings(new QSettings("Test-task", "Settings", this))
    , multicastAddress(QHostAddress("239.255.0.1"))
    , multicastPort(45454)
{
    ui->setupUi(this);
    ui->btnStop->setEnabled(false);

    loadSettings();

    udpSocket->bind(QHostAddress::AnyIPv4, multicastPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(multicastAddress);
}

MainWindow::~MainWindow()
{
    udpSocket->leaveMulticastGroup(multicastAddress);
    sendCommand(QByteArray("STOP"));
    delete ui;
}

void MainWindow::loadSettings()
{
    ui->comboBox->setCurrentText(settings->value("typeC", "std::vector").toString());
    ui->N_spinBox->setValue(settings->value("N", 10).toInt());
    ui->M_spinBox->setValue(settings->value("M", 5).toInt());
    ui->NWrite_spinBox->setValue(settings->value("NWrite", 2).toInt());
    ui->NRead_spinBox->setValue(settings->value("NRead", 2).toInt());
    ui->T1_spinBox->setValue(settings->value("T1", 30).toInt());
    ui->T2_spinBox->setValue(settings->value("T2", 100).toInt());
}

void MainWindow::saveSettings()
{
    settings->setValue("typeC", ui->comboBox->currentText());
    settings->setValue("N", ui->N_spinBox->value());
    settings->setValue("M", ui->M_spinBox->value());
    settings->setValue("NWrite", ui->NWrite_spinBox->value());
    settings->setValue("NRead", ui->NRead_spinBox->value());
    settings->setValue("T1", ui->T1_spinBox->value());
    settings->setValue("T2", ui->T2_spinBox->value());
}

void MainWindow::sendCommand(const QByteArray &data)
{
    udpSocket->writeDatagram(data, multicastAddress, multicastPort);
}

void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    saveSettings();

    QString message = QString("START;%1;%2;%3;%4;%5;%6;%7")
        .arg(ui->comboBox->currentText())
        .arg(ui->N_spinBox->value())
        .arg(ui->M_spinBox->value())
        .arg(ui->NWrite_spinBox->value())
        .arg(ui->NRead_spinBox->value())
        .arg(ui->T1_spinBox->value())
        .arg(ui->T2_spinBox->value());

    sendCommand(message.toUtf8());
}

void MainWindow::on_btnStop_clicked()
{
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    sendCommand(QByteArray("STOP"));
}
