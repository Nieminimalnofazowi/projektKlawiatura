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

private:
    //np imie i nazwisko, nick
    QString userID;
};

#endif // USER_H
