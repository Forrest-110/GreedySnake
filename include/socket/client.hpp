#include <stdio.h> 
#include <string.h>  
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.hpp"

namspace SOCKET{
class clientHandler{
private:
    std::string IP;
    int PORT;
    char read_buffer[1024];
    char write_buffer[1024];
    struct sockaddr_in address;
    int sockfd;
    int len;

public:
    clientHandler(){
        IP = "172.17.0.1";
        PORT = 6789;
        for (int i = 0; i < 1024; i++)
        {
            read_buffer[i] = '\0';
            write_buffer[i] = '\0';
        }
        len=sizeof(address);
    }
    clientHandler(std::string IP, int PORT){
        this->IP = IP;
        this->PORT = PORT;
        for (int i = 0; i < 1024; i++)
        {
            read_buffer[i] = '\0';
            write_buffer[i] = '\0';
        }
        len=sizeof(address);
    }
    void initClientSocket(std::string IP, int PORT){
        this->IP = IP;
        this->PORT = PORT;
        initClientSocket();
    }
    void initClientSocket(void);
    void connectToServer(void);
    void sendMessage(std::string message);
    void readMessage();
    void closeSocket();
    void sendSnakeData(std::string name, int x, int y, SNAKE::Direction dir);
    GridMap parseMapData(std::string message);
    SnakeData parseSnakeData(std::string message);
};
}