#include "map.hpp"
#include "solver.hpp"
#include <unordered_set>
#include <iostream>
using namespace SNAKE;
using namespace TOOL;
using namespace std;
int main()
{
	
	unordered_set<Point,PointHash> walls {
		{5, 0}, {5, 1}, {2, 2}, {5, 2},
		{2, 3}, {5, 3}, {2, 4}, {5, 4}, {2, 5}, {4, 5},
		{5, 5}, {6, 5}, {7, 5}, {2, 6}, {2, 7}};
	GridMap map=GridMap(10,10,walls);
	
	
	Point start {1, 1};
	Point goal {6, 2};
	
    JPSSolver s=JPSSolver(&map,start,goal);
	
	auto came_from = s.jps(start, goal,euclidean);
	
	for (auto& p : came_from) {
		cout << p.first << " " << p.second << endl;
	}
	auto path =reconstruct_path(start, goal, came_from);
	std::cout<<"length of path:"<<path.size()<<std::endl;
	draw_grid(map, {}, {}, path, came_from, start, goal);
}