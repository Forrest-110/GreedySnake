#include "food.hpp"
#include <cstdlib>
bool SNAKE::Food::generateFoodAtXY(int x, int y)
{
    if (map->getCell(x, y) == SNAKE::CellType::EMPTY)
    {
        map->setCellwoUpdate(x, y, SNAKE::CellType::FOOD);
        food_set.insert(Point{x, y, SNAKE::CellType::FOOD});
        return true;
    }
    return false;
}

bool SNAKE::Food::generateFoodRandomly()
{
    int x = rand() % map->getSize();
    int y = rand() % map->getSize();
    return generateFoodAtXY(x, y);
}
bool SNAKE::Food::generateNFoodRandomly(int n)
{
    int count = 0;
    while (count < n)
    {
        if (generateFoodRandomly())
        {
            count++;
        }
    }
    return true;
}
bool SNAKE::Food::removeFoodAtXY(int x, int y)
{
    if (map->getCell(x, y) == SNAKE::CellType::FOOD)
    {
        map->setCellwoUpdate(x, y, SNAKE::CellType::EMPTY);
        food_set.erase(Point{x, y, SNAKE::CellType::FOOD});
        return true;
    }
    return false;
}
bool SNAKE::Food::removeFoodRandomly()
{
    if (food_set.size() == 0)
    {
        return false;
    }
    int index = rand() % food_set.size();
    auto it = food_set.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    Point p = *it;
    return removeFoodAtXY(p.x, p.y);
}
bool SNAKE::Food::removeNFoodRandomly(int n)
{
    int count = 0;
    while (count < n)
    {
        if (removeFoodRandomly())
        {
            count++;
        }
    }
    return true;
}