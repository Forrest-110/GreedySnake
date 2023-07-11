#include "map.hpp"
#include <iostream>
const int TILE_SIZE = 80;

const std::string WALL_IMAGE_PATH = "../img/wall.png";
const std::string EMPTY_IMAGE_PATH = "../img/empty.png";
const std::string FOOD_IMAGE_PATH = "../img/food.png";
const std::string OBSTACLE_IMAGE_PATH = "../img/obstacle.png";
const std::string SNAKERIGHT_IMAGE_PATH = "../img/righthead.png";
const std::string SNAKELEFT_IMAGE_PATH = "../img/lefthead.jpg";
const std::string SNAKEUP_IMAGE_PATH = "../img/uphead.png";
const std::string SNAKEDOWN_IMAGE_PATH = "../img/downhead.jpg";
const std::string SNAKEBODY_IMAGE_PATH = "../img/body.png";

// 游戏图形对象
extern sf::RenderWindow window;
sf::Texture wallTexture;
sf::Texture emptyTexture;
sf::Texture foodTexture;
sf::Texture obstacleTexture;
sf::Texture snakerightTexture;
sf::Texture snakeleftTexture;
sf::Texture snakeupTexture;
sf::Texture snakedownTexture;
sf::Texture snakebodyTexture;
std::vector<sf::Sprite> wallSprites;
std::vector<sf::Sprite> emptySprites;
std::vector<sf::Sprite> foodSprites;
std::vector<sf::Sprite> obstacleSprites;
std::vector<sf::Sprite> snakerightSprites;
std::vector<sf::Sprite> snakeleftSprites;
std::vector<sf::Sprite> snakeupSprites;
std::vector<sf::Sprite> snakedownSprites;
std::vector<sf::Sprite> snakebodySprites;



bool loadGameResources()
{
    if (!wallTexture.loadFromFile(WALL_IMAGE_PATH))
        return false;
    if (!emptyTexture.loadFromFile(EMPTY_IMAGE_PATH))
        return false;
    if (!foodTexture.loadFromFile(FOOD_IMAGE_PATH))
        return false;
    if (!obstacleTexture.loadFromFile(OBSTACLE_IMAGE_PATH))
        return false;
    if (!snakerightTexture.loadFromFile(SNAKERIGHT_IMAGE_PATH))
        return false;
    if (!snakeleftTexture.loadFromFile(SNAKELEFT_IMAGE_PATH))
        return false;
    if (!snakeupTexture.loadFromFile(SNAKEUP_IMAGE_PATH))
        return false;
    if (!snakedownTexture.loadFromFile(SNAKEDOWN_IMAGE_PATH))
        return false;
    if (!snakebodyTexture.loadFromFile(SNAKEBODY_IMAGE_PATH))
        return false;
    return true;
}

// 更新游戏界面
void updateGameWindow()
{
    for (const auto &sprite : wallSprites)
        window.draw(sprite);
    for (const auto &sprite : foodSprites)
        window.draw(sprite);
    for (const auto &sprite : obstacleSprites)
        window.draw(sprite);
    for (const auto &sprite : emptySprites)
        window.draw(sprite);
    for (const auto &sprite : snakerightSprites)
        window.draw(sprite);
    for (const auto &sprite : snakeleftSprites)
        window.draw(sprite);
    for (const auto &sprite : snakeupSprites)
        window.draw(sprite);
    for (const auto &sprite : snakedownSprites)
        window.draw(sprite);
    for (const auto &sprite : snakebodySprites)
        window.draw(sprite);
    window.display();
}

SNAKE::Direction SNAKE::opposite(SNAKE::Direction d){
    switch(d){
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
            return Direction::NONE;
    }
}

void SNAKE::GridMap::init(){
    this->score = 0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if (i==0 || j==0 || i==size-1 || j==size-1)
                map[i][j] = CellType::WALL;
            else
                map[i][j] = CellType::EMPTY;
            // map[i][j] = CellType::EMPTY;
        }
    }
}

void SNAKE::GridMap::update(){
    
    while(!update_queue.empty()){
        auto p = update_queue.front();
        
        update_queue.pop();
        
        map[p.first.x][p.first.y] = p.second;
        
    }
    
}

void SNAKE::GridMap::setCell(int x, int y, CellType type){
    update_queue.push(std::make_pair(Point{x,y,type},type));
}

SNAKE::CellType SNAKE::GridMap::getCell(int x, int y){
    if (!(x < 0 || x >= size || y < 0 || y >= size))
        return map[x][y];
    else{
        std::cout<<x<<","<<y<<" out of range"<<std::endl;
        // exit(0);
        return CellType::OBSTACLE;
    }
}

int SNAKE::GridMap::getSize(){
    
    return size;
}

double SNAKE::GridMap::getGridSize(){
    return grid_size;
}


void SNAKE::GridMap::initui(){
    window.create(sf::VideoMode(this->size * TILE_SIZE, this->size * TILE_SIZE), "Greedy Snake");
    window.setFramerateLimit(60);
    bool resourcesLoaded = loadGameResources();
    if (!resourcesLoaded)
    {
        std::cout << "Failed to load game resources!" << std::endl;
        // 可以在这里添加适当的错误处理逻辑
        return;
    }

}


void SNAKE::GridMap::showMap(SNAKE::Point head1, SNAKE::Point head2, SNAKE::Direction dir1, SNAKE::Direction dir2) const{
    // std::cout << "Score: " << score << std::endl;
    for(int y=0;y<size;y++){
        for(int x=0;x<size;x++){
            std::cout << static_cast<int>(map[x][y]) << " ";
        }
        std::cout << std::endl;
    }
    emptySprites.clear();
    wallSprites.clear();
    foodSprites.clear();
    obstacleSprites.clear();
    snakerightSprites.clear();
    snakeleftSprites.clear();
    snakeupSprites.clear();
    snakedownSprites.clear();
    snakebodySprites.clear();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            sf::Sprite sprite;
            sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            switch (static_cast<int>(map[j][i]))
            {
            case 0:
                sprite.setTexture(emptyTexture);
                emptySprites.push_back(sprite);
                break;
            case 1:
                sprite.setTexture(obstacleTexture);
                obstacleSprites.push_back(sprite);
                break;
            case 2:
                sprite.setTexture(foodTexture);
                foodSprites.push_back(sprite);
                break;
            case 3:
                sprite.setTexture(wallTexture);
                wallSprites.push_back(sprite);
                break;
            case 4:
                if (head1.x == j && head1.y == i){
                    switch(dir1){
                        case Direction::RIGHT:
                            sprite.setTexture(snakerightTexture);
                            snakerightSprites.push_back(sprite);
                            break;
                        case Direction::LEFT:
                            sprite.setTexture(snakeleftTexture);
                            snakeleftSprites.push_back(sprite);
                            break;
                        case Direction::UP:
                            sprite.setTexture(snakeupTexture);
                            snakeupSprites.push_back(sprite);
                            break;
                        case Direction::DOWN:
                            sprite.setTexture(snakedownTexture);
                            snakedownSprites.push_back(sprite);
                            break;
                        default:
                            break;
                    }
                }
                else if (head2.x == j && head2.y == i){
                    switch(dir2){
                        case Direction::RIGHT:
                            sprite.setTexture(snakerightTexture);
                            snakerightSprites.push_back(sprite);
                            break;
                        case Direction::LEFT:
                            sprite.setTexture(snakeleftTexture);
                            snakeleftSprites.push_back(sprite);
                            break;
                        case Direction::UP:
                            sprite.setTexture(snakeupTexture);
                            snakeupSprites.push_back(sprite);
                            break;
                        case Direction::DOWN:
                            sprite.setTexture(snakedownTexture);
                            snakedownSprites.push_back(sprite);
                            break;
                        default:
                            break;
                    }
                }
                else{
                    sprite.setTexture(snakebodyTexture);
                    snakebodySprites.push_back(sprite);
                }
                break;
            }
        }
    }
    updateGameWindow();
}