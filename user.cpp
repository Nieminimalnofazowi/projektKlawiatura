#include "user.h"

user::user()
{

}
/*!
 * Konstruktor obiektu klasy user - zawiera nazwę, którą wpisał użytkownik aplikacji
 */
user::user(QString constructedID)
{
    this->userID = constructedID;
}

user::~user()
{

}

/*!
 * Metoda zapewniająca dostęp do nazwy użytkownika
 */
QString user::getUserID()
{
    return this->userID;
}


