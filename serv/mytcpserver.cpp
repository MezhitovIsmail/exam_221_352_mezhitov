
#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
using namespace std;


MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent), clientCount(0)
{
    // Запуск сервера на порту 33333 и вывод сообщения, если не удалось запустить сервер
    if (!listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server not started!";
        return;
    }
    qDebug() << "Server started!";

    // Устанавливаем связь между сигналом newConnection и слотом slotNewConnection
    connect(this, &MyTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);
}

void MyTcpServer::slotNewConnection(){
    qDebug() << "New user connected!";

    if (clientCount >= 6) {
        qDebug() << "Maximum number of clients reached!";
        return;
    }

    // Получаем указатель на сокет клиента и устанавливаем связь между сигналами readyRead и disconnected и соответствующими слотами
    QTcpSocket* clientSocket = nextPendingConnection();
    clientSockets.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

    clientCount++;
}

void MyTcpServer::slotClientDisconnected(){
    qDebug() << "User disconnected!";
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    clientSockets.removeOne(clientSocket);
    clientSocket->deleteLater();
    clientCount--;
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());

    // Читаем строку из сокета и выводим сообщение о запросе в консоль
    QByteArray requestData = clientSocket->readAll();
    QString request = QString::fromUtf8(requestData);
    request = request.trimmed();
    qDebug() << "Request received from client " << clientSocket->socketDescriptor() << ": " << request;

}


