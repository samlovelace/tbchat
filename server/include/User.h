#ifndef USER_H
#define USER_H

#include <websocketpp/server.hpp>

class User
{
public:
    User(websocketpp::connection_hdl aConnectionHdl);
    ~User();

    std::string getUsername() {return mUsername; }
    void setUsername(std::string aUsername) {mUsername = aUsername; }
    websocketpp::connection_hdl getConnectionHdl() {return mConnectionHdl; }


private:
    std::string mUsername;
    websocketpp::connection_hdl mConnectionHdl; 

};

#endif //USER_H

