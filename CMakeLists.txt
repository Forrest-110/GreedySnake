cmake_minimum_required(VERSION 3.15)
project(GreedySnake)
include_directories(
        include
        include/solver
        include/network
        # include/solver/dqn
)
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIR})
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

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
        src/solver/hamilton.cpp
        src/network/server.cpp
        src/network/client.cpp
)
add_executable(snake run.cpp)
add_executable(test_snake test.cpp)
add_executable(test_solver test_solver.cpp)
add_executable(test_path test_path.cpp)

target_link_libraries(snake ${PROJECT_NAME} yaml-cpp sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(test_snake ${PROJECT_NAME} yaml-cpp sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(test_solver ${PROJECT_NAME} yaml-cpp sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(test_path ${PROJECT_NAME} yaml-cpp sfml-graphics sfml-window sfml-system sfml-network)
