
#include "Server.h"

Server* global_server = nullptr; 

void signal_handler(int signal)
{
    if(global_server != nullptr)
    {
        global_server->stop(); 
    }
    exit(signal); 
}


int main()
{
    Server tbchat;
    global_server = &tbchat;  
    
    std::signal(SIGINT, signal_handler); 
    std::signal(SIGTERM, signal_handler); 
    
    tbchat.run(9002); 

    return 0; 
}