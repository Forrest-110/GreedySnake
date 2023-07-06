#pragma once

#include "base.hpp"
#include "path.hpp"
#include <stdexcept>

namespace SOLVER {

    class HamiltonSolver : public BaseSolver {
    private:
        PathSolver* _path_solver;
        std::vector<std::vector<_TableCell>> _table;
        bool _shortcuts;
        void _build_cycle();
        int _relative_dist(int ori, int x, int size);

    public:
        HamiltonSolver(SNAKE::Snake* snake, PathSolver* p, bool shortcuts = true);
        HamiltonSolver::HamiltonSolver(SNAKE::Snake* snake, PathSolver* p, bool shortcuts) : BaseSolver(snake) {
            _path_solver = p;
            _shortcuts = shortcuts;
            _table.resize(snake->map->getSize(), std::vector<_TableCell>(snake->map->getSize()));
            _build_cycle();
        }
        SNAKE::Direction next_Direction();
    };
}
