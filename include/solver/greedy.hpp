#ifndef _GREEDY_HPP_
#define _GREEDY_HPP_

#include "base.hpp"
#include "path.hpp"

namespace SOLVER{
    class GreedySolver:public BaseSolver{
        private:
        PathSolver *_path_solver;
        public:
        GreedySolver(SNAKE::Snake* snake,PathSolver *p):BaseSolver(snake){
            
            _path_solver=p;
        };
        
        SNAKE::Direction next_Direction();

    };
}

#endif