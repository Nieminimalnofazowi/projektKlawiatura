#ifndef USER_H
#define USER_H

#include<QVector>
#include<QTextStream>
#include<QFile>

class user
{
    //publiczne metody, pola prywatne
public:
    //constr
    user();
    //constructor przeladowanie
    user(QString constructedID);
    //destr
    ~user();
    //metoda pozwalajaca na dostep do ID
    QString getUserID();
    //metoda zapisujaca staty z danej sesji do kolejnego vectora (zwraca result)
    bool saveStats(QVector<int> currentSessionStats);

private:
    //np imie i nazwisko, nick
    QString userID;
    //vector vectorow int -> aby user mogl wypelnic test kilka razy
    QVector< QVector<int> > stats;

};

#endif // USER_H
