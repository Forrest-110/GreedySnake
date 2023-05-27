#ifndef _SERVER_HPP
#define _SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <deque>

namespace SOCKET{

class DataBlock{
    public:
    std::deque<std::string> data;
    DataBlock * another;
    bool occupied;
    DataBlock():occupied(false),another(nullptr){};
};

class DataBlockPair{
    public:
    DataBlock one;
    DataBlock two;
    DataBlockPair(){
        one.another = &two;
        two.another = &one;
    }
    DataBlock *pop(){
        if (!one.occupied){
            one.occupied = true;
            return &one;
        }
        else if (!two.occupied){
            two.occupied = true;
            return &two;
        }
        else{
            return nullptr;
        }
    }
};


class MapData{
    public:
    SNAKE::GridMap map;
    double grid_size;
    MapData(SNAKE::GridMap* m){
        map = *m;
        grid_size = m->getGridSize();
    };
    std::string toString(){
        std::string s = "MAP " + std::to_string(map.getSize()) + " " + std::to_string(grid_size);
        for (int i=0;i<map.getSize();i++){
            for (int j=0;j<map.getSize();j++){
                s = s + " " + std::to_string(int(map.getCell(i,j)));
            }
        }
        return s;
    }
};

class SnakeData{
    public:
    std::string name;
    int score;
    int x;
    int y;
    SNAKE::Direction dir;
    SnakeData(std::string name, int score,int x, int y, SNAKE::Direction dir):name(name),score(score),x(x),y(y),dir(dir){};
    std::string toString(){
        std::string s = "SNAKE "+name + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(int(dir))+ " " + std::to_string(score);
        return s;
    }
};


class serverHandler{
    std::string IP;
    int PORT;
    char read_buffer[1024];
    char write_buffer[1024];
    struct sockaddr_in address;
    struct sockaddr_in client_address;
    int comfd;
    int sockfd;
    int len;
    pthread_t thread_id;
    int ret;
    DataBlockPair data_block_pair;

public:
    serverHandler(){
        IP = "172.17.0.1"
        PORT = 6789;
        for (int i = 0; i < 1024; i++)
        {
            read_buffer[i] = '\0';
            write_buffer[i] = '\0';
        }
        len=sizeof(address);
    };
    serverHandler(std::string ip, int port){
        IP = ip;
        PORT = port;
        for (int i = 0; i < 1024; i++)
        {
            read_buffer[i] = '\0';
            write_buffer[i] = '\0';
        }
        len=sizeof(address);
    };
    void initServerSocket();
    void initServerSocket(std::string ip, int port){
        IP = ip;
        PORT = port;
        initServerSocket();
    }
    void acceptConnection(SNAKE::GridMap *map);
    void sendData(std::string);
    void sendMapData(SNAKE::GridMap *map);
    void sendSnakeData(std::string name, int x, int y, SNAKE::Direction dir);
    void readData();
    void closeSocket();
    void *threadFunction();
};
}

#endif