#pragma once
#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_
#include "map.hpp"
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <math.h>
#include <iostream>
namespace SNAKE{


class BaseSolver{
    protected:
    GridMap *map;
    Point start;
    Point goal;
    std::vector<Point> path;
    public:
    BaseSolver(GridMap *map, Point start, Point goal){
        this->map = map;
        this->start = start;
        this->goal = goal;
    }
    ~BaseSolver(){
        delete map;
    }
    // virtual void solve() = 0;
    std::vector<Point> getPath();

};
class Location{
        public:
        int x;
        int y;
        Location getDirection(){
            if (x==0 && y<0) return {0,-1};
            if (x==0 && y>0) return {0,1};
            if (x>0 && y==0) return {1,0};
            if (x<0 && y==0) return {-1,0};
            return {-1,-1};
        };
        Location():x(0),y(0){};
        Location(Point p):x(p.x),y(p.y){};
        Location(int x, int y):x(x),y(y){};
        ~Location(){};

        bool operator==(const Location& l) const{
            return (x==l.x && y==l.y);
        }
        bool operator!=(const Location& l) const{
            return (x!=l.x || y!=l.y);
        }
        bool operator<(const Location& l) const{
            return std::tie(x, y) < std::tie(l.x, l.y);
        }
        bool operator>(const Location& l) const{
            return std::tie(x, y) > std::tie(l.x, l.y);
        }
        Location operator+(const Location& l) const{
            return {x+l.x, y+l.y};
        }
        Location operator-(const Location& l) const{
            return {x-l.x, y-l.y};
        }
        Location operator-() const{
            return {-x, -y};
        }
        friend std::ostream& operator<<(std::ostream& os, const Location& l);
        
    };
std::ostream& operator<<(std::ostream& os, const SNAKE::Location& l);
struct LocationHash {
    std::size_t operator()(const Location & v) const {
        std::hash<int> hasher;
        std::size_t seed = 0;
        int i=v.x;
        seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        i=v.y;
        seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
        
    }
};
const Location NoneLoc {-1,-1};
const std::vector<Location> ALL_DIRECTIONS={
        {0,-1},
        {0,+1},
        {1,0},
        {-1,0},
    };
class JPSSolver:public BaseSolver{
    
    typedef std::pair<double, Location> PQElement;
    typedef std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> PQLoc;

    typedef double(heuristic_fn)(const Location&, const Location&);
    // private:
    // std::list<Point> openList;
    // std::vector<Point> closeList;
    // int cost=1;
    public:
    JPSSolver(GridMap *map, Point start, Point goal):BaseSolver(map, start, goal){
        ;
    }
    

    Location jump( const Location initial, const Location dir,
	const Location goal);
    std::vector<Location> successors( const Location& current,
	const Location& parent, const Location& goal);
    std::unordered_map<Location, Location,SNAKE::LocationHash> jps(
   
   const Location& start, const Location& goal,
   heuristic_fn heuristic);
    std::vector<Location> pruned_neighbours(const Location& current, const Location& parent) ;
    std::vector<Location> neighbours(const Location& current, const std::vector<Location>& dirs) ;
    bool forced(const Location& loc, const Location& parent, const Location& travel_dir);
    void solve();
    bool valid_move(const Location& current, const Location& dir) {
        
        auto new_loc {current + dir};
        if (new_loc.x < 0 || new_loc.x >= this->map->getSize() || new_loc.y < 0 || new_loc.y >= this->map->getSize()) {
            return false;
        }
        bool ret=((this->map->getCell(new_loc.x,new_loc.y) !=CellType::EMPTY) && (this->map->getCell(new_loc.x,new_loc.y) !=CellType::FOOD));
        
        return !ret;
    }
};
};
namespace TOOL
{
	inline double manhattan(const SNAKE::Location& a, const SNAKE::Location& b) { return abs(a.x - b.x) + abs(a.y - b.y); };
	inline double euclidean(const SNAKE::Location& a, const SNAKE::Location& b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); };
	std::vector<SNAKE::Location> reconstruct_path(
		const SNAKE::Location& start,
		const SNAKE::Location& goal,
		 std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& came_from);

	void draw_grid(
		 SNAKE::GridMap& grid,
		const std::unordered_map<SNAKE::Location, double,SNAKE::LocationHash>& distances = {},
		const std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& point_to = {},
		const std::vector<SNAKE::Location>& path = {},
		const std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& came_from = {},
		const SNAKE::Location& start = SNAKE::NoneLoc,
		const SNAKE::Location& goal = SNAKE::NoneLoc);
};

#endif