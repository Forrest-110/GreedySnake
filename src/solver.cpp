#include "solver.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
typedef std::pair<double, SNAKE::Location> PQElement;
typedef std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> PQLoc;

typedef double(heuristic_fn)(const SNAKE::Location&, const SNAKE::Location&);
std::ostream& SNAKE::operator<<(std::ostream& os, const SNAKE::Location& l)
{
	os << '(' << l.x << ',' << l.y << ')';
	return os;
}

SNAKE::Location SNAKE::JPSSolver::jump( const SNAKE::Location initial, const SNAKE::Location dir,
	const SNAKE::Location goal)
{
	SNAKE::Location new_loc=initial + dir;
	if((this->map->getCell(new_loc.x,new_loc.y) !=SNAKE::CellType::EMPTY) && (this->map->getCell(new_loc.x,new_loc.y) !=SNAKE::CellType::FOOD)){
		return SNAKE::NoneLoc;
	}
	if(new_loc == goal){
		return new_loc;
	}
	for(const auto next : this->pruned_neighbours(new_loc, initial)){
		if(this->forced(next, new_loc, dir)){
			return new_loc;
		}
	}
	if(dir.x == 0 && dir.y >0){
		for(const auto& new_dir: {Location{-1, 0},Location{1,0}}){
			auto jump_point {jump(new_loc, new_dir, goal)};
			if(jump_point != NoneLoc){
				return new_loc;
			}
		}
	}
	if(dir.x == 0 && dir.y <0){
		for(const auto& new_dir: {Location{1, 0},Location{-1,0}}){
			auto jump_point {jump(new_loc, new_dir, goal)};
			if(jump_point != NoneLoc){
				return new_loc;
			}
		}
	}
	// if(dir.x > 0 && dir.y ==0){
	// 	for(const auto& new_dir: {Location{1, 0}}){
	// 		auto jump_point {jump(new_loc, new_dir, goal)};
	// 		if(jump_point != NoneLoc){
	// 			return new_loc;
	// 		}
	// 	}
	// }
	// if(dir.x < 0 && dir.y ==0){
	// 	for(const auto& new_dir: {Location{-1, 0}}){
	// 		auto jump_point {jump(new_loc, new_dir, goal)};
	// 		if(jump_point != NoneLoc){
	// 			return new_loc;
	// 		}
	// 	}
	// }
	if (dir.x!=0&&dir.y!=0)
	exit(0);
	return jump(new_loc, dir, goal);
}


std::vector<SNAKE::Location> SNAKE::JPSSolver::pruned_neighbours(const SNAKE::Location& current, const SNAKE::Location& parent) 
{
	if(parent == SNAKE::NoneLoc){
		
		return this->neighbours(current, SNAKE::ALL_DIRECTIONS);
	}
	
	std::vector<SNAKE::Location> current_neighbours;
	const auto dir {(current - parent).getDirection()};
	
	// Horizontal or vertical neighbour
	{
		// Add natural neighbours
		current_neighbours = neighbours(current, {dir});

		// Add forced neighbours
		const Location inverted_dir {dir.y, dir.x};
		
		if(!valid_move(current, inverted_dir) && valid_move(current, inverted_dir + dir)){
			
			current_neighbours.push_back(current + inverted_dir + dir);
		}
		if(!valid_move(current, -inverted_dir) && valid_move(current, -inverted_dir + dir)){
			
			current_neighbours.push_back(current - inverted_dir + dir);
		}
		if (!valid_move(current-dir, inverted_dir) && valid_move(current-dir, inverted_dir + dir)) {
			
			current_neighbours.push_back(current-dir + inverted_dir + dir);
		}
		if (!valid_move(current-dir, -inverted_dir) && valid_move(current-dir, -inverted_dir + dir)) {
			
			current_neighbours.push_back(current-dir - inverted_dir + dir);
		}
	}
	
	return current_neighbours;
}

std::vector<SNAKE::Location> SNAKE::JPSSolver::neighbours(const SNAKE::Location& current, const std::vector<SNAKE::Location>& dirs) 
{
	std::vector<SNAKE::Location> results;
	for(auto& dir : dirs){
		
		if(this->valid_move(current, dir)){
			
			results.push_back(current + dir);
		}
		
	}
	
	return results;
}

bool SNAKE::JPSSolver::forced(const SNAKE::Location& loc, const SNAKE::Location& parent, const SNAKE::Location& travel_dir) {
	const Location dir {(loc - parent).getDirection()};
	if (dir != travel_dir) {
		
	if(dir!=NoneLoc){
		return true;
	}
	}
	return false;
}

std::vector<SNAKE::Location> SNAKE::JPSSolver::successors( const SNAKE::Location& current,
	const SNAKE::Location& parent, const SNAKE::Location& goal)
{
	
	std::vector<SNAKE::Location> successors;
	auto neighbours {this->pruned_neighbours(current, parent)};
	
	for(const auto& n: neighbours){
		auto jump_point {this->jump( current, (n - current).getDirection(), goal)};
		if(jump_point != NoneLoc){
			successors.push_back(jump_point);
		}
	}
	// std::cout<<"current:"<<current;
	// std::cout<<"neighbours:";
	// for (auto &n:neighbours){
	// 	std::cout<<n;
	// }
	// std::cout<<"successors:";
	// for(auto& s:successors){
	// 	std::cout<<s;
	// }
	
	return successors;
}

std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash> SNAKE::JPSSolver::jps(
   
   const SNAKE::Location& start, const SNAKE::Location& goal,
   heuristic_fn heuristic)
{

	PQLoc open_set;
	std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash> came_from {};
	std::unordered_map<SNAKE::Location, double,SNAKE::LocationHash> cost_so_far {};
	
	open_set.emplace(0, start);
	came_from[start] = start;
	cost_so_far[start] = 0;
	SNAKE::Location parent {SNAKE::NoneLoc};
	
	while(!open_set.empty()){
		
		const auto current {open_set.top().second};
		
		if(current == goal){
			break;
		}

		open_set.pop();
		if(current != start){
			parent = came_from[current];
		}
		
		for(const auto& next : this->successors( current, parent, goal)){
			
			const auto new_cost = cost_so_far[current] + heuristic(current, next);
			auto existing_cost = std::numeric_limits<double>::max();
			if (cost_so_far.count(next)) {
				existing_cost = cost_so_far.at(next);
			}
			if(cost_so_far.find(next) == cost_so_far.end() || new_cost < existing_cost){
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				open_set.emplace(new_cost + heuristic(next, goal), next);
			}
			
		}
	}
	return came_from;
}

std::vector<SNAKE::Location> TOOL::reconstruct_path(
   const SNAKE::Location& start,
   const SNAKE::Location& goal,
   std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& came_from)
{
	std::vector<SNAKE::Location> path {};
	SNAKE::Location current = goal;
	while(current != start){
		path.push_back(current);
		if(came_from.count(current)){
			current = came_from.at(current);
		}
		else{
			// No solution, return empty path
			return {};
		}
	}
	reverse(path.begin(), path.end());
	return path;
}

void TOOL::draw_grid(
   SNAKE::GridMap& grid,
   const std::unordered_map<SNAKE::Location, double,SNAKE::LocationHash>& distances,
   const std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& point_to,
   const std::vector<SNAKE::Location>& path,
   const std::unordered_map<SNAKE::Location, SNAKE::Location,SNAKE::LocationHash>& came_from,
   const SNAKE::Location& start,
   const SNAKE:: Location& goal)
{
	const int field_width = 3;
	std::cout << std::string(field_width * grid.getSize(), '_') << '\n';
	for(int y = 0; y != grid.getSize(); ++y){
		for(int x = 0; x != grid.getSize(); ++x){
			const SNAKE::Location id {x, y};
			if((grid.getCell(id.x,id.y)==SNAKE::CellType::WALL) || (grid.getCell(id.x,id.y)==SNAKE::CellType::OBSTACLE)){
				std::cout << std::string(field_width, '#');
			}
			else if(start != SNAKE::NoneLoc && id == start){
				std::cout << " A ";
			}
			else if(goal != SNAKE::NoneLoc && id == goal){
				std::cout << " Z ";
			}
			else if(!path.empty() && find(path.begin(), path.end(), id) != path.end()){
				std::cout << " @ ";
			}
			else if(came_from.count(id)){
				std::cout << " J ";
			}
			else if(point_to.count(id)){
				const auto next = point_to.at(id);
				if(next.x == x + 1) { std::cout << " > "; }
				else if(next.x == x - 1) { std::cout << " < "; }
				else if(next.y == y + 1) { std::cout << " v "; }
				else if(next.y == y - 1) { std::cout << " ^ "; }
				else { std::cout << " * "; }
			}
			else if(distances.count(id)){
				std::cout << ' ' << std::left << std::setw(field_width - 1) << distances.at(id);
			}
			else{
				std::cout << " . ";
			}
		}
		std::cout << '\n';
	}
	std::cout << std::string(field_width * grid.getSize(), '~') << '\n';
}

