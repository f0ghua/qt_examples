#ifndef STASERVER_H
#define STASERVER_H

#include "staserver_global.h"
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class StaServerPrivate;

class STASERVERSHARED_EXPORT StaServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit StaServer();
    virtual ~StaServer();

protected:
    void incomingConnection(int socketDescriptor);
    StaServerPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(StaServer)
};

#endif // STASERVER_H
