#include "TaskManager.h"
#include "TaskManagerPrivate_p.h"

TaskManager::TaskManager(QObject *parent)
    : QObject(*new TaskManagerPrivate, parent)
{

}

TaskManager::~TaskManager()
{

}

bool TaskManager::addTask(StaClient *client)
{
    Q_D(TaskManager);

    return d->addTask(client);
}

void TaskManager::removeTask(StaClient *client)
{
    Q_D(TaskManager);

    d->removeTask(client);
}

void TaskManager::addTaskAddressMapping(QString sAddr, StaClient *client)
{
    Q_D(TaskManager);

    d->addTaskAddressMapping(sAddr, client);
}

StaClient *TaskManager::getTask(QString sAddr)
{
    Q_D(TaskManager);

    return d->taskMap.value(sAddr);
}


#include "moc_TaskManager.cpp"

