#include "object.hpp"

bool SNAKE::Object::generateObjectAtXY(int x, int y)
{
    if (map->getCell(x, y) == CellType::EMPTY)
    {
        map->setCell(x, y, CellType::OBSTACLE);
        object_set.insert(Point{x, y, CellType::OBSTACLE});
        return true;
    }
    return false;
}

bool SNAKE::Object::generateObjectRandomly()
{
    int x = rand() % map->getSize();
    int y = rand() % map->getSize();
    return generateObjectAtXY(x, y);
}
bool SNAKE::Object::generateNObjectRandomly(int n)
{
    int count = 0;
    while (count < n)
    {
        if (generateObjectRandomly())
        {
            count++;
        }
    }
    return true;
}
bool SNAKE::Object::removeObjectAtXY(int x, int y)
{
    if (map->getCell(x, y) == CellType::OBSTACLE)
    {
        map->setCell(x, y, CellType::EMPTY);
        object_set.erase(Point{x, y, CellType::OBSTACLE});
        return true;
    }
    return false;
}
bool SNAKE::Object::removeObjectRandomly()
{
    if (object_set.size() == 0)
    {
        return false;
    }
    int index = rand() % object_set.size();
    auto it = object_set.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    Point p = *it;
    return removeObjectAtXY(p.x, p.y);
}
bool SNAKE::Object::removeNObjectRandomly(int n)
{
    int count = 0;
    while (count < n)
    {
        if (removeObjectRandomly())
        {
            count++;
        }
    }
    return true;
}