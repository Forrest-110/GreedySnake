cmake_minimum_required(VERSION 3.15)
project(GreedySnake)
include_directories(
        include
)
add_library(${PROJECT_NAME} SHARED
        src/food.cpp
        src/game.cpp
        src/map.cpp
        src/snake.cpp
        src/object.cpp
)
add_executable(snake run.cpp)
add_executable(test_snake test.cpp)
target_link_libraries(snake ${PROJECT_NAME})
target_link_libraries(test_snake ${PROJECT_NAME})