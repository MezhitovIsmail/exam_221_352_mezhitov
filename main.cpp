#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // создает консольное приложение с именем а с параметрами argc и argv
    MyTcpServer myserv;
    return a.exec(); // для запуска программы
}
