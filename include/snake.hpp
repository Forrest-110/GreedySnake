#pragma once
#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include "map.hpp"
#include "food.hpp"
#include <vector>
#include <deque>
#include <cstdlib>
namespace SNAKE
{
    class SnakeBlock{
        protected:
            GridMap* map;
            Food *food;
            int x;
            int y;
            int velocity;
            int lastvelocity;
            SnakeBlock* next;
            SnakeBlock* prev;
        public:
            Direction direction;
            Direction lastdirection;
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
            Point getPoint(){
                return Point(this->x,this->y);
            }
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
            void setMap(GridMap *m){
                this->map=m;
            }
            void setFood(Food *f){
                this->food=f;
            }
            void setFoodMap(GridMap *m){
                food->setMap(m);
            }
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
                // if(x < 0 || x >= this->map->getSize() || y < 0 || y >= this->map->getSize()){
                //     return false;
                // }
                // if (this->map->getCell(x,y) != CellType::EMPTY){
                //     return false;
                // }
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
                this->map->setCell(this->x,this->y,CellType::OCCUPIED);
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
                return false;
            }
    };

    class Snake{
        private:
            
            std::vector<SnakeBlock> body;//body excludes head
            int length;
            int velocity;
            int score;
            
        public:
        GridMap* map;
            Food* food;
            SnakeHead head;
            bool _isDead;
            Snake(GridMap* _map,Food* _food,int x,int y,Direction direction,int velocity,int length = 1):
            head(_map,_food,x,y,direction,velocity),map(_map),food(_food){
                this->length = length;
                this->body.reserve(length-1);
                this->velocity = velocity;
                this->_isDead = false;
                this->map->setCell(x,y,CellType::OCCUPIED);
                this->score = 0;
            }

            Snake(GridMap* _map,Food* _food,Direction direction,int velocity,std::vector<Point> points):
            head(_map,_food,points[0].x,points[0].y,direction,velocity),map(_map),food(_food){
                this->length = points.size();
                this->body.reserve(length-1);
                this->velocity = velocity;
                this->_isDead = false;
                this->map->setCellwoUpdate(points[0].x,points[0].y,CellType::OCCUPIED);
                this->score = 0;
                for (int i=1;i<points.size();i++){
                    this->body.push_back(SnakeBlock(_map,_food,points[i].x,points[i].y,direction,velocity));
                    this->map->setCellwoUpdate(points[i].x,points[i].y,CellType::OCCUPIED);
                }
            }


            void setMap(GridMap *m){
                this->map=m;
                head.setMap(m);
                for (auto b:body){
                    b.setMap(m);
                }
            }
            void setFood(Food *f){
                this->food=f;
                head.setFood(f);
                for (auto b:body){
                    b.setFood(f);
                }
            }
            void setFoodMap(GridMap *m){
                this->food->setMap(m);
                head.setFoodMap(m);
                for (auto b:body){
                    b.setFoodMap(m);
                }
            }
            int getScore(){
                return this->score;
            }
            int getLength(){
                return this->length;
            }
            int getVelocity(){
                return this->velocity;
            };
            Direction getDirection(){
                return this->head.getDirection();
            }
            Direction getLastDirection(){
                return this->head.getLastDirection();
            }
            bool getIsDead(){
                return this->_isDead;
            }
            SnakeHead getHead(){
                return this->head;
            }
            Point getHeadPoint(){
                return this->head.getPoint();
            }
            std::vector<SnakeBlock> getBody(){
                return this->body;
            }
            Point getTail(){
                if (this->body.size() == 0){
                    return this->head.getPoint();
                }
                return this->body.back().getPoint();
            }
            void setLength(int length){
                this->length = length;
            }
           
            void setVelocity(int velocity){
                this->velocity = velocity;
            }
            void setDirection(Direction direction){
                this->head.lastdirection = this->head.direction;
                this->head.direction = direction;
            }
            void setIsDead(bool isDead){
                this->_isDead = isDead;
            }
            void setHead(SnakeHead head){
                this->head = head;
            }
            void setBody(std::vector<SnakeBlock> body){
                this->body = body;
            }

            std::vector<Point> getPoints(){
                std::vector<Point> points;
                points.push_back(this->head.getPoint());
                for (auto b:this->body){
                    points.push_back(b.getPoint());
                }
                return points;
            }

            Snake *getCopy(){
                GridMap *map_copy=new GridMap(*this->map);
                Food *food_copy=new Food(*this->food);
                food_copy->setMap(map_copy);
                Snake *snake_copy=new Snake(map_copy,food_copy,this->getDirection(),this->getVelocity(),this->getPoints());
                snake_copy->score=this->getScore();
                snake_copy->_isDead=this->_isDead;
                return snake_copy;
            }

            Direction changeDirection(Direction direction){
                if (direction == Direction::UP && this->head.lastdirection != Direction::DOWN){
                    return direction;
                }
                if (direction == Direction::DOWN && this->head.lastdirection != Direction::UP){
                    this->head.lastdirection = this->head.direction;
                    return direction;
                }
                if (direction == Direction::LEFT && this->head.lastdirection != Direction::RIGHT){
                    this->head.lastdirection = this->head.direction;
                    return direction;
                }
                if (direction == Direction::RIGHT && this->head.lastdirection != Direction::LEFT){
                    this->head.lastdirection = this->head.direction;
                    return direction;
                }
                return this->head.direction;
            }
            
            bool move();
            bool move(Direction direction);
            
            bool move_along_path(std::deque<Direction> path){
                if (path.size() == 0){
                    return false;
                }
                for (auto direction:path){
                    if (this->move(direction) == false){
                        return false;
                    }
                }
                return true;
            }

    };




}

#endif