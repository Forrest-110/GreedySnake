#include "snake.hpp"
#include <iostream>
SNAKE::Direction SNAKE::GetRandomDirection()
{
        int r = rand() % 4;
        switch (r)
        {
        case 0:
            return Direction::UP;
            break;
        case 1:
            return Direction::DOWN;
            break;
        case 2:
            return Direction::LEFT;
            break;
        case 3:
            return Direction::RIGHT;
            break;
        default:
            return Direction::UP;
            break;
        }
    }
bool SNAKE::Snake::move(SNAKE::Direction direction){
    this->head.move(direction);
    if (this->body.size()!=0)
        this->body[0].move(this->head.getLastDirection());
    for (int i = 1; i < this->body.size() ; i++){
        this->body[i].move(this->body[i - 1].getLastDirection());
    }
    if (this->head.eatFood()){
        this->score++;
        this->map->score++;
        while(!(this->food->generateFoodRandomly()));
        SNAKE::Direction dir_toinsert;
        
        int x_toinsert;
        int y_toinsert;
        SnakeBlock *newblock=nullptr;
        if (this->body.size()!=0){
            dir_toinsert=this->body[this->body.size() - 1].getDirection();
        switch (dir_toinsert){
            case SNAKE::Direction::UP:
                x_toinsert = this->body[this->body.size() - 1].getX();
                y_toinsert = this->body[this->body.size() - 1].getY() + 1;
                break;
            case SNAKE::Direction::DOWN:
                x_toinsert = this->body[this->body.size() - 1].getX();
                y_toinsert = this->body[this->body.size() - 1].getY() - 1;
                break;
            case SNAKE::Direction::LEFT:
                x_toinsert = this->body[this->body.size() - 1].getX() + 1;
                y_toinsert = this->body[this->body.size() - 1].getY();
                break;
            case SNAKE::Direction::RIGHT:
                x_toinsert = this->body[this->body.size() - 1].getX() - 1;
                y_toinsert = this->body[this->body.size() - 1].getY();
                break;
        }
        newblock=new SnakeBlock(this->map,this->food,x_toinsert,y_toinsert,dir_toinsert,
        this->body[this->body.size() - 1].getVelocity(),nullptr,&this->body[this->body.size() - 1]);
        }else{
            dir_toinsert=this->head.getDirection();
            switch (dir_toinsert){
            case SNAKE::Direction::UP:
                x_toinsert = this->head.getX();
                y_toinsert = this->head.getY() + 1;
                break;
            case SNAKE::Direction::DOWN:
                x_toinsert = this->head.getX();
                y_toinsert = this->head.getY() - 1;
                break;
            case SNAKE::Direction::LEFT:
                x_toinsert = this->head.getX() + 1;
                y_toinsert = this->head.getY();
                break;
            case SNAKE::Direction::RIGHT:
                x_toinsert = this->head.getX() - 1;
                y_toinsert = this->head.getY();
                break;
        }
        newblock=new SnakeBlock(this->map,this->food,x_toinsert,y_toinsert,dir_toinsert,
        this->head.getVelocity(),nullptr,&this->head);
        }
        
        this->body.push_back(*newblock);
        delete newblock;
        this->length++;
    }
    if (this->head.isDead()){
        std::cout<<"Snake is dead"<<std::endl;
        this->_isDead = true;
        return false;
    }
    return true;
}

// bool SNAKE::Snake::move(){
    
//     return this->move();
// }