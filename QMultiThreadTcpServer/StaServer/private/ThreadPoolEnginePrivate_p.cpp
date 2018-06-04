#include "ThreadPoolEnginePrivate_p.h"
#include <QDebug>

ThreadPoolEnginePrivate::ThreadPoolEnginePrivate()
{
    nThreads = 20;
}

ThreadPoolEnginePrivate::~ThreadPoolEnginePrivate()
{

}

void ThreadPoolEnginePrivate::init()
{
    for(int i = 0; i < nThreads; i++) {
        QThread *thread = new QThread();
        buf.append(thread);
        free.append(i);
    }
}

QThread *ThreadPoolEnginePrivate::availableThread(int &index)
{
    QThread *thread = NULL;

    index = free.takeAt(0);

    thread = buf.at(index);

    busy.append(index);

    return thread;
}

void ThreadPoolEnginePrivate::putBackThread(int index)
{
    buf.at(index)->terminate();

    int pos = busy.indexOf(index);

    busy.removeAt(pos);

    free.append(index);
}
