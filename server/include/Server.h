#ifndef SERVER_H
#define SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <iostream>
#include <string> 
#include <memory>
#include <nlohmann/json.hpp>
#include "RoomsHandler.h"

using json = nlohmann::json; 
typedef websocketpp::server<websocketpp::config::asio> server;

class Server
{
public:
    Server(/* args */);
    ~Server();

    void run(uint16_t aPortToListenOn); 

private:
    std::unique_ptr<server> mServer;
    std::set<std::shared_ptr<User>> mAllUsers; 
    //std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> mAllUsers;

    // Rooms Handler 
    std::unique_ptr<RoomsHandler> mRoomsHandler; 

    // callback methods 
    void onOpen(websocketpp::connection_hdl hdl); 
    void onClose(websocketpp::connection_hdl hdl); 
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg); 

    // helper functions 
    void sendJson(websocketpp::connection_hdl hdl, const json& msg); 
    std::shared_ptr<User> getUserByConnectionHdl(websocketpp::connection_hdl aHdl);

};

#endif // SERVER_H

