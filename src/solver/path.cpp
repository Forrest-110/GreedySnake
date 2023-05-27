#include "path.hpp"
#include <algorithm>
#include <random>
#include <ctime>

std::deque<SNAKE::Direction> SOLVER::PathSolver::shortest_path_to(Pos des)
{
    this->reset_table();
    SOLVER::Pos head = getSnake()->getHeadPoint();
    table[head.x][head.y].dist = 0;
    std::deque<SOLVER::Pos> queue;
    queue.push_back(head);
    while (!queue.empty())
    {
        SOLVER::Pos cur = queue.front();
        queue.pop_front();
        if (cur == des)
        {
            return build_path(head, des);
        }
        SNAKE::Direction first_dir;
        if (cur == head)
        {
            first_dir = getSnake()->getDirection();
        }
        else
        {
            first_dir = table[cur.x][cur.y].parent.direction_to(cur);
        }
        std::vector<SOLVER::Pos> adjs = cur.all_adjacents();
        std::shuffle(adjs.begin(), adjs.end(), std::default_random_engine(time(NULL)));
        for (int i = 0; i < adjs.size(); i++)
        {
            if (first_dir == cur.direction_to(adjs[i]))
            {
                std::swap(adjs[i], adjs[0]);
                break;
            }
        }
        for (auto adj : adjs)
        {
            if (is_valid(adj))
            {
                
                auto adj_cell = &table[adj.x][adj.y];
                if (adj_cell->dist == INT_MAX)
                {
                    adj_cell->dist = table[cur.x][cur.y].dist + 1;

                    adj_cell->parent = cur;
                    queue.push_back(adj);
                }
            }
        }
    }
    return std::deque<SNAKE::Direction>();
}

std::deque<SNAKE::Direction> SOLVER::PathSolver::longest_path_to(Pos des)
{
    auto path = shortest_path_to(des);
    if (path.empty())
    {
        return path;
    }
    reset_table();
    SOLVER::Pos head = getSnake()->getHeadPoint();
    SOLVER::Pos cur = head;
    table[cur.x][cur.y].visit = true;
    for (auto dir : path)
    {
        cur = cur.adjacent(dir);
        table[cur.x][cur.y].visit = true;
    }
    int idx = 0;
    cur = head;
    while (true)
    {
        auto curr_direction = path[idx];
        auto nxt = cur.adjacent(curr_direction);
        std::vector<SNAKE::Direction> test;
        if (curr_direction == SNAKE::Direction::LEFT || curr_direction == SNAKE::Direction::RIGHT)
        {
            test = {SNAKE::Direction::UP, SNAKE::Direction::DOWN};
        }
        else if (curr_direction == SNAKE::Direction::UP || curr_direction == SNAKE::Direction::DOWN)
        {
            test = {SNAKE::Direction::LEFT, SNAKE::Direction::RIGHT};
        }
        bool extended = false;
        for (auto test_dir : test)
        {
            auto cur_test = cur.adjacent(test_dir);
            auto nxt_test = nxt.adjacent(test_dir);
            if (is_valid(cur_test) && is_valid(nxt_test))
            {
                table[cur_test.x][cur_test.y].visit = true;
                table[nxt_test.x][nxt_test.y].visit = true;
                path.insert(path.begin() + idx, test_dir);
                path.insert(path.begin() + idx + 2, SNAKE::opposite(test_dir));
                extended = true;
                break;
            }
        }
        if (!extended)
        {
            cur = nxt;
            idx++;
            if (idx >= path.size())
            {
                break;
            }
        }
    }
    return path;
}

std::deque<SNAKE::Direction> SOLVER::PathSolver::longest_path_to_tail(){
    auto tail=getSnake()->getTail();
    return path_to(tail,true);
}

std::deque<SNAKE::Direction> SOLVER::PathSolver::shortest_path_to_food(){
    auto food_set=getFood()->food_set;
    int minlen=INT_MAX;
    int tmp;
    std::deque<SNAKE::Direction> ret;
    std::deque<SNAKE::Direction> final_ret;
    for (auto food:food_set){
        ret=path_to(food,false);
        tmp=ret.size();
        if (tmp<minlen){
            minlen=tmp;
            final_ret=ret;
        }
    }
    return final_ret;
}

std::deque<SNAKE::Direction> SOLVER::PathSolver::path_to(Pos des, bool longest){
    SNAKE::CellType orig_type=getMap()->getCell(des.x,des.y);
    getMap()->setCellwoUpdate(des.x,des.y,SNAKE::CellType::EMPTY);
    // std::cout<<"type: "<<(int)orig_type<<std::endl;
    // std::cout<<"new type: "<<(int)getMap()->getCell(des.x,des.y)<<std::endl;
    std::deque<SNAKE::Direction> ret;
    if (longest){
        ret=longest_path_to(des);
    }else{
        ret=shortest_path_to(des);
    }
    getMap()->setCellwoUpdate(des.x,des.y,orig_type);
    
    return ret;
}