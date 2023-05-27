#pragma once
#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <vector>
#include "map.hpp"
#include "greedy.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "object.hpp"
#include "client.hpp"
#include "server.hpp"
#include <string>
namespace SNAKE{

enum class PlayerType{
    Human,
    AI
};

class BasePlayer{
    private:
    PlayerType type;
    public:
    Snake *snake;
    int score;
    public:
    BasePlayer(PlayerType type):type(type){};
    
    PlayerType getType(){
        return type;
    }
    virtual Direction getNextDirection()=0;
};

class Human: public BasePlayer{
    
    
    public:
    Human(Snake *snake):BasePlayer(PlayerType::Human){
        this->score = 0;
        this->snake = snake;
    };
    // ~Human(){
    //     delete snake;
    // };
    Direction getNextDirection();
};

class Ai: public BasePlayer{
    private:
    SOLVER::GreedySolver *greedy_solver;
    public:
    Ai(Snake *snake,SOLVER::GreedySolver *gsolver=nullptr):BasePlayer(PlayerType::AI){
        this->greedy_solver = gsolver;
        this->snake=snake;
    };
    ~Ai(){};
    Direction getNextDirection();
};

class ClientManager{
    public:
    GridMap map;
    Food food;
    Object object;
    BasePlayer mainPlayer;
    BasePlayer anotherPlayer;
    bool isOver;
    std::string name;
    SOCKET::clientHandler client;
    public:
    ClientManager();
    void handleMessageFromServer(string ) ;
    void start(); 
    void run();
    void end();
};

enum class GameMode{
    SinglePlayer,
    MultiPlayer
};

class GameManager{
    public:
    GridMap *map;
    Food *food;
    Object *object;
    std::vector<BasePlayer *> players;
    GameMode mode;
    SOCKET::serverHandler server;
    std::vector<int> clients;
    bool isOver;
    public:
    GameManager(GridMap *map,Food *food,Object *object,BasePlayer *player){
        this->map = map;
        this->food = food;
        this->object = object;
        this->players.push_back(player);
        this->isOver = false;
    };
    GameManager(GridMap *map,Food *food,Object *object,std::vector<BasePlayer *> players){
        this->map = map;
        this->food = food;
        this->object = object;
        this->players = players;
        this->isOver = false;
    };
    void start();
    void run_single_player();
    void run_multi_player();
    void run();
    void end();
};
}


#endif