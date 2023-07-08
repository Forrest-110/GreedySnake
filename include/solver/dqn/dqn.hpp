#ifndef _DQN_HPP_
#define _DQN_HPP_

#include "base.hpp"
#include "path.hpp"

namespace SOLVER{
    class DQNSolver: public BaseSolver{
        public:
        bool _USE_RELATIVE;
        bool _USE_VISUAL_ONLY;
        bool _USE_DDQN;
        bool _USE_DUELING;
        int _EXPLOIT_STEP;
        int _MAX_LEARN_STEP;
        int _RESTORE_STEP;
        double _RWD_EMPTY;
        double _RWD_DEAD;
        double _RWD_FOOD ;
        int _MEM_SIZE;
        int _MEM_BATCH;
        double _EPSILON_MAX;
        double _EPSILON_MIN;
        double _EPSILON_DEC;
        double _LR;
        double _MOMENTUM;
        double _GAMMA;
        double _LEAKY_ALPHA;
        double _TD_UPPER;
        double _TD_LOWER;
        double _PRI_EPSILON;
        double _ALPHA;
        double _BETA_MIN;
        double _BETA_INC;
        int _FREQ_LEARN ;
        int _FREQ_REPLACE;
        int _FREQ_LOG;
        int _FREQ_SAVE;
        int _HISTORY_NUM_AVG;
        std::vector<SNAKE::Direction> SNAKE_ACTIONS;
        int _NUM_ACTIONS;
        public:
        DQNSolver(SNAKE::Snake* snake):BaseSolver(snake){};
        ~DQNSolver(){};
        SNAKE::Direction solve();
        void train();
        void test();
        void save();
        void load();
    };
}

#endif