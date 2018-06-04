#ifndef STACLIENT_H
#define STACLIENT_H

#include <QTcpSocket>
#include <QObject>

class StaClientPrivate;
class TaskManager;

class StaClient : public QTcpSocket
{
    Q_OBJECT
public:
    StaClient(int socketDescriptor, TaskManager *handle);
    virtual ~StaClient();

    int getClientSocketDescriptor();
    QString getClientAdderss();

signals:
    void relay(QString, QByteArray);

protected:
    StaClientPrivate *d_ptr;

private:
    friend class StaClientPrivate;
    Q_PRIVATE_SLOT(d_ptr, void _q_dataRecived())
    Q_PRIVATE_SLOT(d_ptr, void _q_connected())
    Q_PRIVATE_SLOT(d_ptr, void _q_disconnected())
    Q_PRIVATE_SLOT(d_ptr, void _q_clientRelay(QString, QByteArray))
};

#endif // STACLIENT_H
