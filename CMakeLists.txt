cmake_minimum_required(VERSION 3.15)
project(GreedySnake)
include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)
add_library(${PROJECT_NAME} SHARED
        src/food.cpp
        src/game.cpp
        src/map.cpp
        src/snake.cpp
        src/object.cpp
)
add_executable(snake run.cpp)
target_link_libraries(snake ${PROJECT_NAME})