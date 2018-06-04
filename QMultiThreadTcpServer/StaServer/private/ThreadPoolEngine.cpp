#include "ThreadPoolEngine.h"
#include "ThreadPoolEnginePrivate_p.h"

ThreadPoolEngine::ThreadPoolEngine(QObject *parent)
    : QObject(*new ThreadPoolEnginePrivate, parent)
{
    Q_D(ThreadPoolEngine);

    d->init();
}

ThreadPoolEngine::~ThreadPoolEngine()
{

}

int ThreadPoolEngine::getAvailableThreadCount()
{
    Q_D(ThreadPoolEngine);

    return d->free.size();
}

int ThreadPoolEngine::getUsedThreadCount()
{
    Q_D(ThreadPoolEngine);

    return d->busy.size();
}

QThread *ThreadPoolEngine::getAvailableThread(int &index)
{
    Q_D(ThreadPoolEngine);

    return d->availableThread(index);
}

void ThreadPoolEngine::putBackThread(int index)
{
    Q_D(ThreadPoolEngine);

    return d->putBackThread(index);
}

#include "moc_ThreadPoolEngine.cpp"
