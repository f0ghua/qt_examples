#include "StaClient.h"
#include "StaClientPrivate_p.h"
#include <QDebug>

StaClient::StaClient(int socketDescriptor, TaskManager *handle)
    : d_ptr(new StaClientPrivate(handle, this))
{
    setSocketDescriptor(socketDescriptor);
    d_ptr->init(socketDescriptor);
}

StaClient::~StaClient()
{

}

int StaClient::getClientSocketDescriptor()
{
    return d_ptr->descriptor;
}

QString StaClient::getClientAdderss()
{
    return d_ptr->sAddress;
}

#include "moc_StaClient.cpp"
