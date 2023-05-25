#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include "map.hpp"
#include "food.hpp"
#include <vector>

namespace SNAKE
{
    enum class Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Direction GetRandomDirection(){
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



    class SnakeBlock{
        protected:
            GridMap* map;
            Food *food;
            int x;
            int y;
            Direction direction;
            Direction lastdirection;
            int velocity;
            int lastvelocity;
            SnakeBlock* next;
            SnakeBlock* prev;
        public:
            SnakeBlock(GridMap*_map,Food* _food, int x,int y,Direction direction,int velocity,
            SnakeBlock* next = nullptr,SnakeBlock* prev = nullptr){
                this->map = _map;
                this->food = _food;
                this->x = x;
                this->y = y;
                this->direction = direction;
                this->lastdirection = direction;
                this->velocity = velocity;
                this->lastvelocity = velocity;
                this->map->setCell(x,y,CellType::OCCUPIED);
                this->next = next;
                this->prev = prev;
            };
            int getX(){
                return this->x;
            };
            int getY(){
                return this->y;
            };
            Direction getDirection(){
                return this->direction;
            };
            Direction getLastDirection(){
                return this->lastdirection;
            };
            int getVelocity(){
                return this->velocity;
            };
            int getLastVelocity(){
                return this->lastvelocity;
            };
            SnakeBlock* getNext(){
                return this->next;
            };
            SnakeBlock* getPrev(){
                return this->prev;
            };
            void setXY(int x,int y){
                this->x = x;
                this->y = y;
                this->map->setCell(x,y,CellType::OCCUPIED);
            };
            
            void setDirection(Direction direction){
                this->lastdirection = this->direction;
                this->direction = direction;
            };
            void setVelocity(int velocity){
                this->lastvelocity = this->velocity;
                this->velocity = velocity;
            };
            bool move(){
                switch (this->direction)
                {
                case Direction::UP:
                    this->map->setCell(this->x,this->y,CellType::EMPTY);
                    this->y -= this->velocity;
                    if (checkXY(this->x,this->y) == false){
                        this->y += this->velocity;
                        this->map->setCell(this->x,this->y,CellType::OCCUPIED);
                        return false;
                    }
                    break;
                case Direction::DOWN:
                    this->map->setCell(this->x,this->y,CellType::EMPTY);
                    this->y += this->velocity;
                    if (checkXY(this->x,this->y) == false){
                        this->y -= this->velocity;
                        this->map->setCell(this->x,this->y,CellType::OCCUPIED);
                        return false;
                    }
                    break;
                case Direction::LEFT:
                    this->map->setCell(this->x,this->y,CellType::EMPTY);
                    this->x -= this->velocity;
                    if (checkXY(this->x,this->y) == false){
                        this->x += this->velocity;
                        this->map->setCell(this->x,this->y,CellType::OCCUPIED);
                        return false;
                    }
                    break;
                case Direction::RIGHT:
                    this->map->setCell(this->x,this->y,CellType::EMPTY);
                    this->x += this->velocity;
                    if (checkXY(this->x,this->y) == false){
                        this->x -= this->velocity;
                        this->map->setCell(this->x,this->y,CellType::OCCUPIED);
                        return false;
                    }
                    break;
                default:
                    break;
                }
                this->map->setCell(this->x,this->y,CellType::OCCUPIED);
                return true;
            };
            bool move(Direction direction){
                this->lastdirection = this->direction;
                this->direction = direction;
                return this->move();
            };
            bool checkXY(int x,int y){
                if(x < 0 || x >= this->map->getSize() || y < 0 || y >= this->map->getSize()){
                    return false;
                }
                if (this->map->getCell(x,y) != CellType::EMPTY){
                    return false;
                }
                return true;
            };

            

            
            
    };


    class SnakeHead: public SnakeBlock{
        public:
            SnakeHead(GridMap*_map,Food* _food, int x,int y,Direction direction,int velocity,
            SnakeBlock* next = nullptr,SnakeBlock* prev = nullptr):SnakeBlock(_map,_food,x,y,direction,velocity,next,prev){
            };
            bool isFood(){
                if (this->map->getCell(this->x,this->y) == CellType::FOOD){
                    return true;
                }
                return false;
            };

            bool eatFood(){
                if (this->isFood() == false){
                    return false;
                }
                this->food->removeFoodAtXY(this->x,this->y);
                return true;
            };

            bool isSelf(){
                if (this->map->getCell(this->x,this->y) == CellType::OCCUPIED){
                    return true;
                }
                return false;
            };

            bool isDead(){
                if (this->isSelf() == true){
                    return true;
                }
                if (this->map->getCell(this->x,this->y) == CellType::WALL){
                    return true;
                }
                if (this->map->getCell(this->x,this->y) == CellType::OBSTACLE){
                    return true;
                }

            }
    };

    class Snake{
        private:
            GridMap* map;
            Food* food;
            SnakeHead head;
            std::vector<SnakeBlock> body;//body includes head
            int length;
            int velocity;
            Direction direction;
            Direction lastdirection;
            
        public:
            bool isDead;
            Snake(GridMap* _map,Food* _food,int x,int y,Direction direction,int velocity,int length = 1):
            head(_map,_food,x,y,direction,velocity),map(_map),food(_food){
                this->length = length;
                this->body.reserve(length);
                this->velocity = velocity;
                this->direction = direction;
                this->lastdirection = direction;
                this->isDead = false;
                this->map->setCell(x,y,CellType::OCCUPIED);
                this->body.push_back(this->head);
            }
            int getLength(){
                return this->length;
            }
            int getVelocity(){
                return this->velocity;
            };
            Direction getDirection(){
                return this->direction;
            }
            Direction getLastDirection(){
                return this->lastdirection;
            }
            bool getIsDead(){
                return this->isDead;
            }
            SnakeHead getHead(){
                return this->head;
            }
            std::vector<SnakeBlock> getBody(){
                return this->body;
            }
            void setLength(int length){
                this->length = length;
            }
           
            void setVelocity(int velocity){
                this->velocity = velocity;
            }
            void setDirection(Direction direction){
                this->lastdirection = this->direction;
                this->direction = direction;
            }
            void setIsDead(bool isDead){
                this->isDead = isDead;
            }
            void setHead(SnakeHead head){
                this->head = head;
            }
            void setBody(std::vector<SnakeBlock> body){
                this->body = body;
            }
            void changeDirection(Direction direction){
                if (direction == Direction::UP && this->lastdirection != Direction::DOWN){
                    this->lastdirection = this->direction;
                    this->direction = direction;
                }
                if (direction == Direction::DOWN && this->lastdirection != Direction::UP){
                    this->lastdirection = this->direction;
                    this->direction = direction;
                }
                if (direction == Direction::LEFT && this->lastdirection != Direction::RIGHT){
                    this->lastdirection = this->direction;
                    this->direction = direction;
                }
                if (direction == Direction::RIGHT && this->lastdirection != Direction::LEFT){
                    this->lastdirection = this->direction;
                    this->direction = direction;
                }
            }
            
            bool move();
            bool move(Direction direction);

    };




}

#endif