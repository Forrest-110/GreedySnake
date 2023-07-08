#ifndef _HAMILTON_HPP_
#define _HAMILTON_HPP_

#include "base.hpp"
#include "path.hpp"

namespace SOLVER{
    class __TableCell{
        public:
        int idx;
        SNAKE::Direction direc;
        public:
        void reset(){
            idx=-1;
            direc=SNAKE::Direction::NONE;
        }
        __TableCell(){
            reset();
        }
    };

    class HamiltonSolver:public BaseSolver{
        private:
        PathSolver *_path_solver;
        bool _shortcuts;
        std::vector<std::vector<__TableCell>> _table;
        public:
        void build_cycle();
        HamiltonSolver(SNAKE::Snake* snake,PathSolver *p,bool shortcuts=true):BaseSolver(snake){
            _path_solver=p;
            _shortcuts=shortcuts;
            int size=snake->map->getSize();
            if (size % 2 != 0){
                std::cout<<"HamiltonSolver: map size must be even"<<std::endl;
                exit(1);
            }
            _table.resize(size);
            for(int i=0;i<size;i++){
                _table[i].resize(size);
            }
            build_cycle();
        };
        std::vector<std::vector<__TableCell>> getTable(){
            return _table;
        }
        SNAKE::Direction next_Direction();
        int relative_distance(int ori,int x,int size){
            if (ori>x)
            x+=size;
            return x-ori;
        }
        void reset_goal(){
            
            build_cycle();
        }
    };





}



#endif