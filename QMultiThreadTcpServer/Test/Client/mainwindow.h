#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void catchSendButtonClickedSlot();
    void clientConnect();
    void clientDisconnected();
    void clientReady();
    void clientBytesWritten(qint64 bytes);

private:
    QTcpSocket *client;
    int addr;

    QLineEdit *dataEdit;
};

#endif // MAINWINDOW_H
