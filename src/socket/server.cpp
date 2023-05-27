#include "server.hpp"
#include <iostream>
#include <cstdio>
void SOCKET::serverHandler::initServerSocket(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    std::cout << "Socket created successfully" << std::endl;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr(IP.c_str());
    ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (ret < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }
    std::cout << "Binding successful" << std::endl;
    ret = listen(sockfd, 5);
    if (ret != 0)
    {
        perror("ERROR on listening");
        exit(1);
    }
    std::cout << "Listening successful" << std::endl;

}

void SOCKET::serverHandler::acceptConnection(SNAKE::GridMap *map){
    while (1){
comfd = accept(sockfd, (struct sockaddr *)&client_address, (socklen_t *)&len);
    if (comfd < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }
    std::cout << "Connection accepted" << std::endl;
    sendMapData(map);
    ret=pthread_create(&thread_id,NULL,serverHandler::threadFunction,(void*)this);
    if(ret!=0){
        perror("ERROR on thread creation");
        exit(1);
    }
    std::cout << "Thread created" << std::endl;
    pthread_detach(thread_id);
    }
}



void SOCKET::serverHandler::sendData(std::string &data){
    std::cout << "Sending data to client : " << data << std::endl;
    memset(write_buffer, 0, sizeof(write_buffer));
    strcpy(write_buffer, data.c_str());
    send(comfd, write_buffer, sizeof(write_buffer),0);
}

void SOCKET::serverHandler::sendMapData(SNAKE::GridMap *map){
    SOCKET::mapData map_data(map);
    std::cout << "Sending map data to client : " << std::endl;
    sendData(map_data.toString());
}

void SOCKET::serverHandler::sendSnakeData(std::string name, int x, int y, SNAKE::Direction dir, int score){
    SOCKET::snakeData snake_data(name,score,x,y,dir);
    std::cout << "Sending snake data to client : " << std::endl;
    sendData(snake_data.toString());
}

void SOCKET::serverHandler::readData(){
    memset(read_buffer, 0, sizeof(read_buffer));
    recv(comfd, read_buffer, sizeof(read_buffer),0);
    std::cout << "Data received from client : " << read_buffer << std::endl;
}

void SOCKET::serverHandler::closeSocket(){
    
    close(sockfd);
    std::cout << "Socket closed" << std::endl;
}

void *SOCKET::serverHandler::threadFunction(){

    DataBlock* data_block = data_block_pair.pop();
    if (!data_block)
    return NULL;
    std::cout << "Thread function called" << std::endl;
    while (1)
    {
        readData();
        DataBlock* another_block=data_block->another;
        while (!another_block->data.empty()){;}
        another_block->data.push_back(read_buffer);
        memset(read_buffer, 0, sizeof(read_buffer));
        while (!data_block->data.empty()){
            sendData(data_block->data.front());
            data_block->data.pop_front();
        }
    }

    close(comfd);
    return NULL;
}