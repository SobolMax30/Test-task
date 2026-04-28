#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QStringListModel>

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
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnClear_clicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QStringListModel *logModel;
    QStringList logLines;

    void addLogLine(QString text);
};

#endif
