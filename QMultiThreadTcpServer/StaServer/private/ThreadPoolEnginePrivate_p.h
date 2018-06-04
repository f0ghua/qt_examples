#ifndef THREADPOOLENGINEPRIVATE_P_H
#define THREADPOOLENGINEPRIVATE_P_H

#include <QtCore/private/qobject_p.h>
#include "ThreadPoolEngine.h"
#include <QList>

class ThreadPoolEnginePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(ThreadPoolEngine)
public:
    ThreadPoolEnginePrivate();
    virtual ~ThreadPoolEnginePrivate();

    void init();

    QThread *availableThread(int &index);
    void putBackThread(int index);

    QList<QThread *> buf;
    QList<int> free;
    QList<int> busy;
    int nThreads;
};

#endif // THREADPOOLENGINEPRIVATE_P_H
