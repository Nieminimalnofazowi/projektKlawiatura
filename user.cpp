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


