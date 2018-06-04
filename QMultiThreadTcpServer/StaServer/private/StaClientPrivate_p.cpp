#include "StaClientPrivate_p.h"
#include "TaskManager.h"
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

StaClientPrivate::StaClientPrivate(TaskManager *handle, StaClient *parent)
    : q_ptr(parent), handle(handle)
{

}

StaClientPrivate::~StaClientPrivate()
{

}

void StaClientPrivate::init(int sd)
{
    descriptor = sd;

    QObject::connect(q_ptr, SIGNAL(connected()), q_ptr, SLOT(_q_connected()));
    QObject::connect(q_ptr, SIGNAL(readyRead()), q_ptr, SLOT(_q_dataRecived()));
    QObject::connect(q_ptr, SIGNAL(disconnected()), q_ptr, SLOT(_q_disconnected()));

    QObject::connect(q_ptr, SIGNAL(relay(QString, QByteArray)),
                     q_ptr, SLOT(_q_clientRelay(QString, QByteArray)));
}

void StaClientPrivate::_q_connected()
{

}

void StaClientPrivate::_q_dataRecived()
{
    QByteArray baData = q_ptr->readAll();

    if(baData.at(0) == 0x01) {
        sAddress = QString(baData.remove(0, 1));
        handle->addTaskAddressMapping(sAddress, q_ptr);
        qDebug() << sAddress;
    } else {
        emit handle->getTask(QString(baData))->relay(QString(baData), baData);
    }
}

void StaClientPrivate::_q_disconnected()
{
    qDebug() << "server" << "disconnected" << descriptor << sAddress;
    handle->removeTask(q_ptr);
    q_ptr->deleteLater();
}

void StaClientPrivate::_q_clientRelay(QString sAddr, QByteArray baData)
{
    if(QString::compare(sAddr, sAddress) == 0) {
        q_ptr->write(baData);
    }
}

