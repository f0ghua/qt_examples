#ifndef TASKMANAGERPRIVATE_H
#define TASKMANAGERPRIVATE_H

#include <QtCore/private/qobject_p.h>
#include "TaskManager.h"
#include <QMap>
#include <QReadWriteLock>

class ThreadPoolEngine;

class TaskManagerPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(TaskManager)
public:
    TaskManagerPrivate();
    virtual ~TaskManagerPrivate();

    bool addTask(StaClient *client);
    void removeTask(StaClient *client);
    void addTaskAddressMapping(QString sAddr, StaClient *client);

    ThreadPoolEngine *tpEngine;

    QReadWriteLock mthreadGuard;
    QMap<int/*描述符*/, int/*线程索引*/> threadMap;

    QReadWriteLock mtaskGuard;
    QMap<QString, StaClient *> taskMap;
};

#endif // TASKMANAGERPRIVATE_H
