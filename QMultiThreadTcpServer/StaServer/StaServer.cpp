#include "StaServer.h"
#include "StaServerPrivate_p.h"

StaServer::StaServer()
    : d_ptr(new StaServerPrivate())
{
    Q_D(StaServer);

    d->q_ptr = this;
}

StaServer::~StaServer()
{
    delete d_ptr;
}

void StaServer::incomingConnection(int socketDescriptor)
{
    Q_D(StaServer);

    d->incomingConnection(socketDescriptor);
}

#include "moc_StaServer.cpp"
