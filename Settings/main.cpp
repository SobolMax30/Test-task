#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Настройки");
    w.resize(800, 500);
    w.show();
    return a.exec();
}
