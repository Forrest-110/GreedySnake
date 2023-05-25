#include "snake.hpp"

bool SNAKE::Snake::move(){
    this->head.move(this->direction);
    for (int i = 0; i < this->length ; i++){
        this->body[i].move(this->body[i + 1].getLastDirection());
    }
    if (this->head.eatFood()){
        this->length++;
        SNAKE::Direction dir_toinsert=this->body[this->length - 1].getDirection();
        int x_toinsert;
        int y_toinsert;
        switch (dir_toinsert){
            case SNAKE::Direction::UP:
                x_toinsert = this->body[this->length - 1].getX();
                y_toinsert = this->body[this->length - 1].getY() + 1;
                break;
            case SNAKE::Direction::DOWN:
                x_toinsert = this->body[this->length - 1].getX();
                y_toinsert = this->body[this->length - 1].getY() - 1;
                break;
            case SNAKE::Direction::LEFT:
                x_toinsert = this->body[this->length - 1].getX() + 1;
                y_toinsert = this->body[this->length - 1].getY();
                break;
            case SNAKE::Direction::RIGHT:
                x_toinsert = this->body[this->length - 1].getX() - 1;
                y_toinsert = this->body[this->length - 1].getY();
                break;
        }
        SnakeBlock newblock=SnakeBlock(this->map,this->food,x_toinsert,y_toinsert,dir_toinsert,
        this->body[this->length - 1].getVelocity(),nullptr,&this->body[this->length - 1]);
        this->body.push_back(newblock);
    }
    if (this->head.isDead()){
        this->isDead = true;
        return false;
    }

}

bool SNAKE::Snake::move(SNAKE::Direction direction){
    this->direction = direction;
    return this->move();
}