#ifndef USER_H
#define USER_H

#include<QVector>
#include<QTextStream>
#include<QFile>
/*!
 * \brief Klasa user obsługuje tworzonych użytkowników
 */
class user
{
    //publiczne metody, pola prywatne
public:
    //constr
    user();
    /*!
     * \brief Konstruktor przeładowany
     * \param Nazwa użytkownika
     */
    user(QString constructedID);
    //destr
    ~user();
    /*!
     * \brief Metoda pozwalająca na dostęp do userID
     * \return Zwraca nazwę użytkownika
     */
    QString getUserID();

private:
    /*!
     * \brief Nazwa użytkownika
     */
    QString userID;
};

#endif // USER_H
