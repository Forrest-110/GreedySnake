#include "map.hpp"
#include "solver.hpp"
#include <unordered_set>
using namespace SNAKE;
using namespace TOOL;
using namespace std;
int main()
{
	unordered_set<Location> walls {
		{5, 0}, {5, 1}, {2, 2}, {5, 2},
		{2, 3}, {5, 3}, {2, 4}, {5, 4}, {2, 5}, {4, 5},
		{5, 5}, {6, 5}, {7, 5}, {2, 6}, {2, 7}};
	GridMap map {10, 10, walls};

	Location start {1, 1};
	Location goal {6, 2};
    JPSSolver s=JPSSolver(&map,(Point)start,(Point)goal);
	auto came_from = s.jps(map, start, goal,euclidean);
	auto path =reconstruct_path(start, goal, came_from);
	draw_grid(map, {}, {}, path, came_from, start, goal);
}