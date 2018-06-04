#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>

class StaClient;
class TaskManagerPrivate;

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = 0);
    virtual ~TaskManager();

    bool addTask(StaClient *client);
    void removeTask(StaClient *client);
    void addTaskAddressMapping(QString sAddr, StaClient *client);
    StaClient *getTask(QString sAddr);

private:
    Q_DECLARE_PRIVATE(TaskManager)
};

#endif // TASKMANAGER_H
