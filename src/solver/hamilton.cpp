#include "hamilton.hpp"

namespace SOLVER {

class _TableCell {
public:
    int idx;
    SNAKE::Direction direc;

    _TableCell() : idx(-1), direc(SNAKE::Direction::NONE) {}

    void reset() {
        idx = -1;
        direc = SNAKE::Direction::NONE;
    }
};

void HamiltonSolver::_build_cycle() {
    // 获取地图大小和蛇的长度
    int size = snake->map->getSize();
    int snakeLength = snake->getLength();

    // 初始化哈密顿环索引
    int index = 0;

    // 获取蛇头和蛇尾的位置
    SNAKE::Point head = snake->getHeadPoint();
    SNAKE::Point tail = snake->getTail();

    // 构建哈密顿环路径
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            _table[row][col].idx = index;

            // 设置方向为 NONE
            _table[row][col].direc = SNAKE::Direction::NONE;

            // 将蛇头位置对应的表格单元的方向设置为蛇头的方向
            if (row == head.x && col == head.y) {
                _table[row][col].direc = snake->getDirection();
            }

            // 将蛇尾位置对应的表格单元的方向设置为蛇的最后移动方向
            if (row == tail.x && col == tail.y) {
                _table[row][col].direc = snake->getLastDirection();
            }

            index++;
        }
    }

    // 处理蛇身体部分
    SNAKE::SnakeBlock* bodyPart = snake->getBody().data();
    for (int i = 0; i < snakeLength - 1; i++) {
        int row = bodyPart[i].getX();
        int col = bodyPart[i].getY();

        _table[row][col].idx = index;
        _table[row][col].direc = bodyPart[i].getDirection();

        index++;
    }
    
}
int HamiltonSolver::_relative_dist(int ori, int x, int size) {
    if (ori > x) {
        x += size;
    }
    return x - ori;
}


 SNAKE::Direction HamiltonSolver::next_Direction() {
        SNAKE::Point head = snake->getHeadPoint();
        auto map = snake->map;
        auto table = _table;
        SNAKE::Direction nxt_direction = table[head.x][head.y].direc;
        // 当蛇长度不太长时，可以选择捷径
        if (_shortcuts && snake->getLength() < 0.5 * map->getSize()) {
            std::vector<SNAKE::Point> path = _path_solver->shortest_path_to_food();
            if (!path.empty()) {
                SNAKE::Point tail = snake->getTail();
                //添加一个adj函数
                SNAKE::Point nxt = head.adj(path[0]);
                //要添加一个getFoodLocation函数
                SNAKE::Point food = map->getFoodLocation();
                int tail_idx = table[tail.x][tail.y].idx;
                int head_idx = table[head.x][head.y].idx;
                int nxt_idx = table[nxt.x][nxt.y].idx;
                int food_idx = table[food.x][food.y].idx;

            // 排除一个特殊情况
            if (!(path.size() == 1 && abs(food_idx - tail_idx) == 1)) {
                int head_idx_rel = _relative_dist(tail_idx, head_idx, map->getSize());
                int nxt_idx_rel = _relative_dist(tail_idx, nxt_idx, map->getSize());
                int food_idx_rel = _relative_dist(tail_idx, food_idx, map->getSize());

                if (!path.empty() && nxt_idx_rel > head_idx_rel && nxt_idx_rel <= food_idx_rel) {
                    nxt_direction = path[0];
                }
            }
            }
        }   

    return nxt_direction;
}




} // namespace SOLVER
