#pragma once
#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <vector>
#include "map.hpp"
#include "greedy.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "object.hpp"
#include <thread>
#include <chrono>
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
    
    char up,down,left,right;
    
    public:
    Human(Snake *snake):BasePlayer(PlayerType::Human){
        this->score = 0;
        this->snake = snake;
        this->up = 'w';
        this->down = 's';
        this->left = 'a';
        this->right = 'd';
    };
    Human(Snake *snake,char up,char down,char left,char right):BasePlayer(PlayerType::Human){
        this->score = 0;
        this->snake = snake;
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
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


class GameManager{
    public:
    GridMap *map;
    Food *food;
    Object *object;
    std::vector<BasePlayer *> players;
    std::vector<std::thread *> threads;
    bool isOver;
    public:
    GameManager(GridMap *map,Food *food,Object *object,BasePlayer *player){
        this->map = map;
        this->food = food;
        this->object = object;
        this->players.push_back(player);
        this->threads.push_back(nullptr);
        this->isOver = false;
    };
    GameManager(GridMap *map,Food *food,Object *object,std::vector<BasePlayer *> players){
        this->map = map;
        this->food = food;
        this->object = object;
        this->players = players;
        for (auto player:players){
            this->threads.push_back(nullptr);
        }
        this->isOver = false;
    };
    // ~GameManager(){
    //     delete map;
    //     delete food;
    //     delete object;
    //     for (auto player:players){
    //         delete player;
    //     }
    // };
    void start();
    void run();
    void thread_run(BasePlayer* player);
    void end();
    void stop(){
        while (this->isOver==false)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};
}


#endif