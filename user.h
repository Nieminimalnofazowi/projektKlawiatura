#ifndef USER_H
#define USER_H

#include<QVector>
#include<QTextStream>
#include<QFile>

class user
{
    //publiczne metody, pola prywatne
public:
    user();
    //constructor przeladowanie
    user(QString constructedID);
    ~user();
    //metoda pozwalajaca na dostep do ID
    QString getUserID();
    //metoda zapisujaca staty z danej sesji do kolejnego vectora (zwraca result)
    bool saveStats(QVector<int> currentSessionStats);
    //zapis calosci do pliku (?)
    bool saveStatsToFile();
private:
    //np imie i nazwisko, nick
    QString userID;
    //vector vectorow int -> aby user mogl wypelnic test kilka razy
    QVector< QVector<int> > stats;

};

#endif // USER_H
