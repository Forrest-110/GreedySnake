#ifndef _GREEDY_HPP_
#define _GREEDY_HPP_

#include "base.hpp"
#include "path.hpp"

namespace SOLVER{
    class GreedySolver:public BaseSolver{
        private:
        PathSolver _path_solver;
        public:
        GreedySolver(SNAKE::GridMap *m,SNAKE::Snake* snake,SNAKE::Food *f):BaseSolver(m,snake,f){
            _path_solver=PathSolver(m,snake,f);
        };
        ~GreedySolver(){
        };
        SNAKE::Direction next_Direction();

    };
}

#endif