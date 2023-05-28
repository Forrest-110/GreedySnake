cmake_minimum_required(VERSION 3.15)
project(GreedySnake)
include_directories(
        include
        include/solver
        # include/solver/dqn
)
add_library(${PROJECT_NAME} SHARED
        src/food.cpp
        src/game.cpp
        src/map.cpp
        src/snake.cpp
        src/object.cpp
        src/visualize.cpp
        src/solver/base.cpp
        src/solver/path.cpp
        src/solver/greedy.cpp
)
add_executable(snake run.cpp)
add_executable(test_snake test.cpp)
add_executable(test_solver test_solver.cpp)
add_executable(test_path test_path.cpp)
target_link_libraries(test_solver ${PROJECT_NAME})
target_link_libraries(snake ${PROJECT_NAME})
target_link_libraries(test_snake ${PROJECT_NAME})
target_link_libraries(test_path ${PROJECT_NAME})
