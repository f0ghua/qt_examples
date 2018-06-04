#include "mainwindow.h"
#include <QPushButton>
#include <QHostAddress>
#include <QHBoxLayout>
#include <QTime>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6666);
    connect(client, SIGNAL(connected()), this, SLOT(clientConnect()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(client, SIGNAL(readyRead()), this, SLOT(clientReady()));
    connect(client, SIGNAL(bytesWritten(qint64)),
            this, SLOT(clientBytesWritten(qint64)));

    dataEdit = new QLineEdit(this);
    QPushButton *sendButton = new QPushButton(QString::fromUtf8("发送"), this);
    connect(sendButton, SIGNAL(clicked()),
            this, SLOT(catchSendButtonClickedSlot()));

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(dataEdit);
    hlayout->addWidget(sendButton);
    setLayout(hlayout);
}

Widget::~Widget()
{

}

void Widget::catchSendButtonClickedSlot()
{
    client->write(dataEdit->text().toLocal8Bit().data());
}

void Widget::clientConnect()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    addr = qrand()%300;
    QByteArray ba;
    ba.append(0x01);
    ba.append(QString::number(addr));
    qDebug() << "client" << "connected" << addr;
    client->write(ba);
}

void Widget::clientDisconnected()
{
    qDebug() << "disconnect";
}

void Widget::clientReady()
{
    qDebug() << "client" << addr;
    while(client->bytesAvailable()) {
        qDebug() << client->readAll();
    }
}

void Widget::clientBytesWritten(qint64 bytes)
{
    qDebug() << bytes;
}
