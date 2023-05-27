#include "client.hpp"


void SOCKET::clientHandler::initClientSocket(void)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "Fail to create a socket. Error: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Socket successfully created.." << std::endl;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr(IP.c_str());
}

void SOCKET::clientHandler::connectToServer(void)
{
    int ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (ret == -1)
    {
        std::cout << "Connection to the server failed. Error: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Connected to the server.." << std::endl;
    }
}

void SOCKET::clientHandler::sendMessage(std::string &message)
{
    memset(write_buffer, 0, sizeof(write_buffer));
    strcpy(write_buffer, message.c_str());
    send(sockfd, write_buffer, sizeof(write_buffer),0);
}

void SOCKET::clientHandler::readMessage()
{
    memset(read_buffer, 0, sizeof(read_buffer));
    recv(sockfd, read_buffer, sizeof(read_buffer),0);
}

void SOCKET::clientHandler::closeSocket()
{
    close(sockfd);
}

void SOCKET::clientHandler::sendSnakeData(std::string name, int x, int y, SNAKE::Direction dir)
{
    SOCKET::snakeData snake_data(name, x, y, dir);
    std::cout << "Sending snake data to server : " << std::endl;
    sendMessage(snake_data.toString());
}

SNAKE::GridMap SOCKET::clientHandler::parseMapData(std::string message){
    std::vector<std::string> tokens;
    std::stringstream check1(message);
    std::string intermediate;
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    if (tokens[0]!="MAP" )
    {
        std::cout << "Error in parsing map data" << std::endl;
        exit(EXIT_FAILURE);
    }
    int size=std::stoi(tokens[1]);
    double grid_size=std::stod(tokens[2]);
    std::vector<std::vector<int>> grid;
    for (int i = 0; i < size; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < size; j++)
        {
            row.push_back(std::stoi(tokens[3+i*size+j]));
        }
        grid.push_back(row);
    }
    SNAKE::GridMap ret(size,grid_size,grid);
    return ret;
    
}

SnakeData SOCKET::clientHandler::parseSnakeData(std::string message){
    std::vector<std::string> tokens;
    std::stringstream check1(message);
    std::string intermediate;
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    if (tokens[0]!="SNAKE" || tokens.size()!=6)
    {
        std::cout << "Error in parsing snake data" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string name = tokens[1];
    int x = std::stoi(tokens[2]);
    int y = std::stoi(tokens[3]);
    SNAKE::Direction dir = static_cast<SNAKE::Direction>(std::stoi(tokens[4]));
    int score = std::stoi(tokens[5]);
    SnakeData snake_data(name,score,x,y,dir);
    return snake_data;
}