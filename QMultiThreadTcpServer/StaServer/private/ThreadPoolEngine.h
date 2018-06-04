#ifndef THREADPOOLENGINE_H
#define THREADPOOLENGINE_H

#include <QObject>
#include <QThread>

class ThreadPoolEnginePrivate;

class ThreadPoolEngine : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPoolEngine(QObject *parent = 0);
    virtual ~ThreadPoolEngine();

    int getAvailableThreadCount();
    int getUsedThreadCount();

    QThread *getAvailableThread(int &index);
    void putBackThread(int index);

private:
    Q_DECLARE_PRIVATE(ThreadPoolEngine)
};

#endif // THREADPOOLENGINE_H
