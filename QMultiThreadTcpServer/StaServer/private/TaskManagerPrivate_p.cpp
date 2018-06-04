#include "TaskManagerPrivate_p.h"
#include "ThreadPoolEngine.h"
#include "StaClient.h"
#include <QWriteLocker>

TaskManagerPrivate::TaskManagerPrivate()
{
    Q_Q(TaskManager);

    tpEngine = new ThreadPoolEngine(q);
}

TaskManagerPrivate::~TaskManagerPrivate()
{

}

bool TaskManagerPrivate::addTask(StaClient *client)
{
    QWriteLocker locker(&mthreadGuard);
    QThread *thread = NULL;

    if(tpEngine->getAvailableThreadCount() == 0) {
        qDebug() << QString::fromUtf8("线程池已用完，断开与客户端的连接");
        return false;
    } else {
        int index = -1;
        thread = tpEngine->getAvailableThread(index);
        client->moveToThread(thread);
        thread->start();

        threadMap.insert(client->socketDescriptor(), index);
        taskMap.insert("1", client);
    }

    return true;
}

void TaskManagerPrivate::removeTask(StaClient *client)
{
    {
        QWriteLocker locker(&mthreadGuard);

        int index = threadMap.value(client->getClientSocketDescriptor());
        threadMap.remove(client->getClientSocketDescriptor());

        tpEngine->putBackThread(index);
    }

    {
        QWriteLocker locker(&mtaskGuard);
        taskMap.remove(client->getClientAdderss());
    }
}

void TaskManagerPrivate::addTaskAddressMapping(QString sAddr, StaClient *client)
{
    QWriteLocker locker(&mtaskGuard);
    taskMap.insert(sAddr, client);
}

