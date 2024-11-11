
#include "RoomsHandler.h"
#include <iostream>

RoomsHandler::RoomsHandler()
{
    // for testing 
    std::shared_ptr<Room> test = std::make_shared<Room>("testing"); 
    mRooms.push_back(test); 

    std::shared_ptr<Room> another = std::make_shared<Room>("general"); 
    mRooms.push_back(another); 
}

RoomsHandler::~RoomsHandler()
{

}

bool RoomsHandler::addUserToRoom(std::shared_ptr<User> aUser, std::string aRoomName)
{
    auto room = getRoomFromName(aRoomName); 

    room->addUser(aUser); 
    std::cout << "Added user: " << aUser->getUsername() << " to room: " << room->name() << std::endl; 

    return true; 
}

std::vector<std::shared_ptr<User>> RoomsHandler::getRoomMembers(std::string aRoomName)
{
    auto room = getRoomFromName(aRoomName); 

    return room->members(); 
}

std::vector<std::string> RoomsHandler::getRoomNames()
{
    std::vector<std::string> roomNames; 

    for(auto& room : mRooms)
    {
        roomNames.push_back(room->name()); 
    }

    return roomNames; 
}

std::shared_ptr<Room> RoomsHandler::getRoomFromName(std::string aRoomName)
{
    for(auto& room : mRooms)
    {
        if(aRoomName == room->name())
        {
            return room;
        }
    }

    return nullptr; 
}




