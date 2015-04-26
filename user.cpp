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


