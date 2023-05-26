#pragma once
#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <vector>
#include "map.hpp"
#include "greedy.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "object.hpp"
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
    ~BasePlayer(){};
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
    ~Human(){
        delete snake;
    };
    Direction getNextDirection();
};

class Ai: public BasePlayer{
    private:
    SOLVER::GreedySolver *greedy_solver;
    public:
    Ai(SOLVER::GreedySolver *gsolver=nullptr):BasePlayer(PlayerType::AI){
        this->greedy_solver = gsolver;
    };
    ~Ai(){};
    Direction getNextDirection();
};


class GameManager{
    public:
    GridMap *map;
    Food *food;
    Object *object;
    std::vector<BasePlayer *> players;
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
    ~GameManager(){
        delete map;
        delete food;
        delete object;
        for (auto player:players){
            delete player;
        }
    };
    void start();
    void run();
    void end();
};
}


#endif