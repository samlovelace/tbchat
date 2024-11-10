#ifndef SERVER_H
#define SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <iostream>
#include <string> 
#include <memory>

typedef websocketpp::server<websocketpp::config::asio> server;

class Server
{
public:
    Server(/* args */);
    ~Server();

    void run(uint16_t aPortToListenOn); 



private:
    std::unique_ptr<server> mServer;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> mConnections;

    // callback methods 
    void onOpen(websocketpp::connection_hdl hdl); 
    void onClose(websocketpp::connection_hdl hdl); 
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg); 

};

#endif // SERVER_H

