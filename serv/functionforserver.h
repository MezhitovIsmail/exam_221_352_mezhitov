#ifndef FUNCTIONFORSERVER_H
#define FUNCTIONFORSERVER_H


#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QString>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QStandardItemModel>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

QByteArray parsing (QString data_from_client,int desc);
#endif // FUNCTIONFORSERVER_H
