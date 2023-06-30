#include "functionforserver.h"
#include <QStandardItemModel>
#include <QFile>

QByteArray max_price()
{
    std::map<int, QString> dict;
    QString res = "";
    QFile file("/home/kim/Desktop/exam_30_07_2023/products.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        QTextStream in(&file);
        int maximum = -1;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            for (int i = 0; i < line.split(",").size(); i++)
            {
                if (((QString)line.split(",")[2]).toInt() > maximum)
                    maximum = ((QString)line.split(",")[2]).toInt();
                dict[((QString)line.split(",")[2]).toInt()] = (QString)line.split(",")[0];

            }
        }
        for(auto& item : dict)
        {
            if (maximum == item.first)
                res += (QString)item.second;
        }
}
    file.close();
    res += '\n';
    return res.toUtf8();

}

QByteArray expensive()
{
    int summ = 0;
    int count = 0;
    QString res = "";
    std::map<int, QString> dict;
    QFile file("/home/kim/Desktop/exam_30_07_2023/products.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "File not exists";
    } else {
            QTextStream in(&file);
            while (!in.atEnd())
            {

                QString line = in.readLine();
                for (int i = 0; i < line.split(",").size(); i++)
                {
                    summ +=((QString)line.split(",")[2]).toInt();
                    count++;
                    dict[((QString)line.split(",")[2]).toInt()] = (QString)line.split(",")[0];
            }
                float middle = (float)summ / count;

                for(auto& item : dict)
                {
                    if (middle < item.first)
                    {

                    qDebug() << item.second;
                    res += (QString)item.second + '\n';
                    }

                }
            }
    }
    file.close();
    return res.toUtf8();
}


QByteArray max_price_in_type(QString type)
{
    qDebug() << type;
    QList<int> li;
    QFile file("/home/kim/Desktop/exam_30_07_2023/products.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "File not exists";
    } else {
            QTextStream in(&file);
            while (!in.atEnd())
            {

                QString line = in.readLine();
                for (int i = 0; i < line.split(",").size(); i++)
                {
                    if ((QString)line.split(",")[1] == type)
                    {
                        li.append(((QString)line.split(",")[2]).toInt());
                    }
                }
                }
    }
    double max = *std::max_element(li.begin(), li.end());
    qDebug() << max;
    QString s = QString::number(max) + '\n';
    file.close();
    return s.toUtf8();

}

QByteArray expensive_in_type(QString type)
{
    QString res = "";
    int summ = 0, count = 0;
    float middle = 0;
    std::map<QString, int> dict;
    QFile file("/home/kim/Desktop/exam_30_07_2023/products.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
                qDebug() << "File not exists";
    } else {
                QTextStream in(&file);
                while (!in.atEnd())
                {

                QString line = in.readLine();
                for (int i = 0; i < line.split(",").size(); i++)
                {
                    if (type == (QString)line.split(",")[1])
                    {
                        summ +=((QString)line.split(",")[2]).toInt();
                        count++;
                        dict[(QString)line.split(",")[0]] = ((QString)line.split(",")[2]).toInt();
                    }
                }
                }
    }
    middle = float(summ) / count;
    for(auto& item : dict)
    {
                if (middle < item.second)
                qDebug() << item.first;
                res += item.first + " ";
    }
    res += '\n';
    file.close();
    return res.toUtf8();
}


QByteArray parsing(QString data_from_client,int desc)
{
    if (data_from_client.trimmed() == "max_price")
    {
        return max_price();
    }
    if (data_from_client.trimmed() == "expensive")
    {
        return expensive();
    }
    if(data_from_client.contains('&'))
    {
        QString type;
        QStringList data_from_client_list = data_from_client.trimmed().split(QLatin1Char('&'));
        if(data_from_client_list.front() == "max_price_in_type"){
                data_from_client_list.pop_front();
                type = data_from_client_list.front();
                return max_price_in_type(type);
        }
        if(data_from_client_list.front() == "expensive_in_type"){
                data_from_client_list.pop_front();
                type = data_from_client_list.front();
                return expensive_in_type(type);
        }

    }
}
