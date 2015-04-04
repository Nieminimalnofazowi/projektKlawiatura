#include "user.h"

user::user()
{

}

user::user(QString constructedID)
{
    this->userID = constructedID;
}

user::~user()
{

}

QString user::getUserID()
{
    return this->userID;
}

bool user::saveStats(QVector<int> currentSessionStats)
{
    this->stats.append(currentSessionStats);
    return 1;
}

bool user::saveStatsToFile()
{
    QFile plikWynikowy("C:\\Results.txt");
    if(!plikWynikowy.open(QIODevice::ReadWrite | QIODevice::Text))
        return 0;
    QTextStream out(&plikWynikowy);
    QTextStream in(&plikWynikowy);
    //sprawdzam zawartosc pliku
    QString temp = in.readAll();
    if(temp.contains(this->userID))
    {

    }
    plikWynikowy.close();
    return 1;
}


