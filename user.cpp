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
    QFile plikWynikowy("Results.txt");
    if(!plikWynikowy.open(QIODevice::ReadWrite | QIODevice::Text))
        return 0;
    QTextStream out(&plikWynikowy);
    QTextStream in(&plikWynikowy);
    //sprawdzam zawartosc pliku
    QString temp = in.readAll();
    if(temp.contains(this->userID))
    {
        int tempElement = temp.indexOf(this->userID,0); //szukamy userID od pierwszego znaku
        tempElement += this->userID.length(); //wyliczam za ktora litera stringu mam wstawic wyniki
        //stworzenie stringu wynikow
        QString tempStats;
        for(int i = 0 ; i<stats.size() ; i++)
        {
            for(int j = 0 ; j<stats[i].length() ; j++)
            {
                tempStats = tempStats + " " + QString::number(stats[i][j]); //jeden ciag danych
            }
            tempStats += "\n"; //new line
        }
        //za chwile
        temp.insert(tempElement,tempStats);
    }
    out << temp; //wgrywamy z powrotem do pliku to co bylo i dopisano
    plikWynikowy.close();
    return 1;
}


