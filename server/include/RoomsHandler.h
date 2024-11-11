#ifndef ROOMSHANDLER_H
#define ROOMSHANDLER_H

#include "Room.h"
#include <map>
#include <string> 
#include <nlohmann/json.hpp>

using json = nlohmann::json; 

class RoomsHandler
{
public:
    RoomsHandler(/* args */);
    ~RoomsHandler();

    std::vector<std::string> getRoomNames(); 
    bool addUserToRoom(std::shared_ptr<User> aUser, std::string aRoomName); 
    std::vector<std::shared_ptr<User>> getRoomMembers(std::string aRoomName); 
    std::vector<json> getRoomChatHistory(std::string aRoomName); 
    void appendRoomChatHistory(std::string aRoomName, json aJsonMsg); 

private:
    std::vector<std::shared_ptr<Room>> mRooms;  

    std::shared_ptr<Room> getRoomFromName(std::string aRoomName); 

};
#endif // ROOMSHANDLER_H

