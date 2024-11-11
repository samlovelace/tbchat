#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "User.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json; 

class Room
{
public:
    Room(std::string aRoomName);
    ~Room();

    std::string name() {return mName;}
    std::vector<std::shared_ptr<User>> members() {return mMembers; }
    void addUser(std::shared_ptr<User> aUser) {mMembers.push_back(aUser); }
    void appendChatHistory(json aJsonMsg) {mChatHistory.push_back(aJsonMsg); }
    std::vector<json> getChatHistory() {return mChatHistory; }


private:
    std::string mName; 
    std::vector<std::shared_ptr<User>> mMembers;
    std::vector<json> mChatHistory; 

};
#endif // ROOM_H