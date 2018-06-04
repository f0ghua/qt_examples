#include "mainwindow.h"
#include <QHostAddress>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    server = new StaServer();
    qDebug() << server->listen(QHostAddress("127.0.0.1"), 6666);
}

MainWindow::~MainWindow()
{

}
