#ifndef STACLIENTPRIVATE_H
#define STACLIENTPRIVATE_H

#include "StaClient.h"

class TaskManager;

class StaClientPrivate
{
public:
    StaClientPrivate(TaskManager *handle, StaClient *parent = 0);
    virtual ~StaClientPrivate();

    void init(int sd);

    void _q_connected();
    void _q_dataRecived();
    void _q_disconnected();
    void _q_clientRelay(QString sAddr, QByteArray baData);

    StaClient *q_ptr;

    QString sAddress;
    int descriptor;
    TaskManager *handle;

    friend class StaClient;
};

#endif // STACLIENTPRIVATE_H
