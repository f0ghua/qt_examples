#ifndef STASERVERPRIVATE_H
#define STASERVERPRIVATE_H

#include <QtCore/private/qobject_p.h>
#include "../StaServer.h"
#include "StaClient.h"

class TaskManager;

class StaServerPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(StaServer)
public:
    StaServerPrivate();
    virtual ~StaServerPrivate();

    void incomingConnection(int socketDescriptor);

    TaskManager *taskManager;
};

#endif // STASERVERPRIVATE_H
