#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_
#include "map.hpp"
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
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
    virtual ~BaseSolver(){
        delete map;
    }
    virtual void solve() = 0;
    virtual std::vector<Point> getPath() = 0;

};
class Location{
        public:
        Point p;
        Location getDirection(){
            if (p.x==0 && p.y<0) return {0,-1};
            if (p.x==0 && p.y>0) return {0,1};
            if (p.x>0 && p.y==0) return {1,0};
            if (p.x<0 && p.y==0) return {-1,0};
            return {-1,-1};
        };
        Location(Point p):p(p){};
        Location(int x, int y):p({x,y}){};
        bool operator==(const Location& l) const{
            return (p==l.p );
        }
        bool operator!=(const Location& l) const{
            return (p.x!=l.p.x || p.y!=l.p.y);
        }
        bool operator<(const Location& l) const{
            return std::tie(p.x, p.y) < std::tie(l.p.x, l.p.y);
        }
        bool operator>(const Location& l) const{
            return std::tie(p.x, p.y) > std::tie(l.p.x, l.p.y);
        }
        Location operator+(const Location& l) const{
            return {p.x+l.p.x, p.y+l.p.y};
        }
        Location operator-(const Location& l) const{
            return {p.x-l.p.x, p.y-l.p.y};
        }
        Location operator-() const{
            return {-p.x, -p.y};
        }
        
    };
const Location NoneLoc {-1,-1};
std::vector<Location> ALL_DIRECTIONS={
        {0,-1},
        {0,+1},
        {1,0},
        {-1,0},
    };
class JPSSolver:public BaseSolver{
    
    typedef std::pair<double, Location> PQElement;
    typedef std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> PQLoc;

    typedef double(heuristic_fn)(const Location&, const Location&);
    private:
    std::list<Point> openList;
    std::vector<Point> closeList;
    int cost=1;
    public:
    JPSSolver(GridMap *map, Point start, Point goal):BaseSolver(map, start, goal){
        ;
    }
    

    Location jump( GridMap &grid, const Location initial, const Location dir,
	const Location goal);
    std::vector<Location> successors( GridMap & grid, const Location& current,
	const Location& parent, const Location& goal);
    std::unordered_map<Location, Location> jps(
   GridMap & grid,
   const Location& start, const Location& goal,
   heuristic_fn heuristic);
    std::vector<Location> pruned_neighbours(const Location& current, const Location& parent) ;
    std::vector<Location> neighbours(const Location& current, const std::vector<Location>& dirs) ;
    bool forced(const Location& loc, const Location& parent, const Location& travel_dir);
    void solve();
    bool valid_move(const Location& current, const Location& dir) {
        auto new_loc {current + dir};
        return ((this->map->getCell(new_loc.p.x,new_loc.p.y) !=CellType::EMPTY) && (this->map->getCell(new_loc.p.x,new_loc.p.y) !=CellType::FOOD));
    }
};
};
namespace TOOL
{
	inline double manhattan(const SNAKE::Location& a, const SNAKE::Location& b) { return abs(a.p.x - b.p.x) + abs(a.p.y - b.p.y); };
	inline double euclidean(const SNAKE::Location& a, const SNAKE::Location& b) { return sqrt((a.p.x - b.p.x) * (a.p.x - b.p.x) + (a.p.y - b.p.y) * (a.p.y - b.p.y)); };
	std::vector<SNAKE::Location> reconstruct_path(
		const SNAKE::Location& start,
		const SNAKE::Location& goal,
		const std::unordered_map<SNAKE::Location, SNAKE::Location>& came_from);

	void draw_grid(
		 SNAKE::GridMap& grid,
		const std::unordered_map<SNAKE::Location, double>& distances = {},
		const std::unordered_map<SNAKE::Location, SNAKE::Location>& point_to = {},
		const std::vector<SNAKE::Location>& path = {},
		const std::unordered_map<SNAKE::Location, SNAKE::Location>& came_from = {},
		const SNAKE::Location& start = SNAKE::NoneLoc,
		const SNAKE::Location& goal = SNAKE::NoneLoc);
};

#endif