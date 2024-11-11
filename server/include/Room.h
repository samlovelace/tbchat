#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "User.h"

class Room
{
public:
    Room(std::string aRoomName);
    ~Room();

    std::string name() {return mName;}
    std::vector<std::shared_ptr<User>> members() {return mMembers; }
    void addUser(std::shared_ptr<User> aUser) {mMembers.push_back(aUser); }

private:
    std::string mName; 
    std::vector<std::shared_ptr<User>> mMembers;

};
#endif // ROOM_H