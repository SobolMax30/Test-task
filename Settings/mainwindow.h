#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QSettings>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QSettings *settings;
    QHostAddress multicastAddress;
    quint16 multicastPort;

    void loadSettings();
    void saveSettings();
    void sendCommand(const QByteArray &data);
};

#endif // MAINWINDOW_H
