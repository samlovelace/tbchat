
#include "Server.h"

Server::Server() : mServer(std::make_unique<server>()), mRoomsHandler(std::make_unique<RoomsHandler>())
{
    mServer->init_asio(); 

    mServer->set_open_handler(std::bind(&Server::onOpen, this, std::placeholders::_1)); 
    mServer->set_close_handler(std::bind(&Server::onClose, this, std::placeholders::_1));
    mServer->set_message_handler(std::bind(&Server::onMessage, this, std::placeholders::_1, std::placeholders::_2));

}

Server::~Server()
{
}

void Server::run(uint16_t aPortToListenOn)
{
    mServer->listen(aPortToListenOn); 
    mServer->start_accept(); 

    std::cout << "!!!!!!!!!!!!! tbchat started on ws://localhost:" << std::to_string(aPortToListenOn) << " !!!!!!!!!!!!!!" << std::endl; 

    mServer->run();  
}

void Server::onOpen(websocketpp::connection_hdl hdl)
{
    std::shared_ptr<User> usr = std::make_shared<User>(hdl); 
    mAllUsers.insert(usr);
}

void Server::onClose(websocketpp::connection_hdl hdl)
{
    auto usr = getUserByConnectionHdl(hdl); 

    if(nullptr != usr)
    {
        mAllUsers.erase(usr);
    } 
}

void Server::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    std::string recvd_msg = msg->get_payload(); 
    std::cout << "Recvd msg: " << recvd_msg << std::endl; 

    json json_msg = json::parse(recvd_msg);

    if(json_msg["action"] == "get_rooms")
    {
        // get the vector of rooms from RoomsHandler
        std::vector<std::string> rooms = mRoomsHandler->getRoomNames(); 
        
        // convert to json and send to connection
        json response = {
                {"action", "room_list"},
                {"rooms", rooms }
        };

        sendJson(hdl, response);
    }
    else if (json_msg["action"] == "join")
    {
        // get the user and set the username
        auto usr = getUserByConnectionHdl(hdl); 
        usr->setUsername(json_msg["username"]); 

        // get the name of the room we are adding the user to
        std::string roomName = json_msg["room"]; 
        mRoomsHandler->addUserToRoom(usr, roomName); 
    }
    else if (json_msg["action"] == "message")
    {
        std::string roomName = json_msg["room"]; 

        std::vector<std::shared_ptr<User>> roomMembers = mRoomsHandler->getRoomMembers(roomName); 

        for(auto& member : roomMembers)
        {
            sendJson(member->getConnectionHdl(), json_msg); 
        }
    }

}

void Server::sendJson(websocketpp::connection_hdl hdl, const json& msg)
{
    std::string toSend = msg.dump(); 

    mServer->send(hdl, toSend, websocketpp::frame::opcode::text); 
}

std::shared_ptr<User> Server::getUserByConnectionHdl(websocketpp::connection_hdl aHdl)
{
    // TODO: refactor this to better handle if we cant find a User with the hdl

    // Find the User instance with the matching connection handle
    auto it = std::find_if(mAllUsers.begin(), mAllUsers.end(), [&aHdl](std::shared_ptr<User> user) {
        return user->getConnectionHdl().lock() == aHdl.lock();
    });

    if(it == mAllUsers.end())
    {
        std::cout << "Could not find User with specified connection_hdl!" << std::endl;
        return nullptr;   
    }

    // return the
    return *it; 
}
