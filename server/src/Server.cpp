
#include "Server.h"

Server::Server() : mServer(std::make_unique<server>())
{
    mServer->init_asio(); 

    mServer->set_open_handler(std::bind(&Server::onOpen, this, std::placeholders::_1)); 
    mServer->set_close_handler(std::bind(&Server::onClose, this, std::placeholders::_1));
    mServer->set_message_handler(std::bind(&Server::onMessage, this, std::placeholders::_1, std::placeholders::_2));

}

Server::~Server()
{
}

void Server::onOpen(websocketpp::connection_hdl hdl)
{
    mConnections.insert(hdl);
}

void Server::onClose(websocketpp::connection_hdl hdl)
{
    mConnections.erase(hdl); 
}

void Server::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    std::string recvd_msg = msg->get_payload(); 

    for(auto& conn : mConnections)
    {
        mServer->send(conn, recvd_msg, websocketpp::frame::opcode::text);
    }
}

void Server::run(uint16_t aPortToListenOn)
{
    mServer->listen(aPortToListenOn); 
    mServer->start_accept(); 

    std::cout << "!!!!!!!!!!!!! tbchat started on ws://localhost:" << std::to_string(aPortToListenOn) << " !!!!!!!!!!!!!!" << std::endl; 

    mServer->run();  
}