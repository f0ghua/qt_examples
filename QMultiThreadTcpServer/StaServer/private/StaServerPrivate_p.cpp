#include "StaServerPrivate_p.h"
#include "TaskManager.h"
#include "StaClient.h"
#include <QThread>
#include <QDebug>

StaServerPrivate::StaServerPrivate()
{
    Q_Q(StaServer);

    taskManager = new TaskManager(q);
}

StaServerPrivate::~StaServerPrivate()
{

}

void StaServerPrivate::incomingConnection(int socketDescriptor)
{
    StaClient *client = new StaClient(socketDescriptor, taskManager);
    if(!taskManager->addTask(client)) {
        qDebug() << QString::fromUtf8("断开建立的连接");
        client->deleteLater();
    }
}

