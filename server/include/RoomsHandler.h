#ifndef ROOMSHANDLER_H
#define ROOMSHANDLER_H

#include "Room.h"
#include <map>
#include <string> 

class RoomsHandler
{
public:
    RoomsHandler(/* args */);
    ~RoomsHandler();

    std::vector<std::string> getRoomNames(); 
    std::shared_ptr<Room> getRoomFromName(std::string aRoomName); 
    bool addUserToRoom(std::shared_ptr<User> aUser, std::string aRoomName); 
    std::vector<std::shared_ptr<User>> getRoomMembers(std::string aRoomName); 

private:
    std::vector<std::shared_ptr<Room>> mRooms;  
};
#endif // ROOMSHANDLER_H

