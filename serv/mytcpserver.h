#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

private slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QList<QTcpSocket*> clientSockets;
    int clientCount;
};

#endif // MYTCPSERVER_H
