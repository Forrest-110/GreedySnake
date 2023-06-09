#include "map.hpp"
#include "visualize.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "object.hpp"
#include "game.hpp"
#include "network/server.hpp"
#include "network/client.hpp"
#include <conio.h>
#include <yaml-cpp/yaml.h>
using namespace SNAKE;
using namespace SOLVER;

struct Options{
    int map_size;
    enum struct MODE{ single,multi, ai } game_mode;
    enum struct SPEED{ low, medium, high } game_speed;
    int food_num;
    int object_num;

    enum struct AIsolver{ greedy, hamilton } ai_solver;
    enum struct SERVER_OR_CLIENT{ server, client } server_or_client;
    

};

Options readFromArg(int argc, char** argv){
    Options options;
    if (argc==1){
        //默认参数
        options.map_size=10;
        options.game_mode=Options::MODE::ai;
        options.game_speed=Options::SPEED::medium;
        options.food_num=1;
        options.object_num=1;
        options.ai_solver=Options::AIsolver::hamilton;
        options.server_or_client=Options::SERVER_OR_CLIENT::server;
    }else if (argc==2){
        //读取配置文件
        YAML::Node config = YAML::LoadFile(argv[1]);
        options.map_size=config["map_size"].as<int>();
        options.game_mode=static_cast<Options::MODE>(config["game_mode"].as<int>());
        options.game_speed=static_cast<Options::SPEED>(config["game_speed"].as<int>());
        options.food_num=config["food_num"].as<int>();
        options.object_num=config["object_num"].as<int>();
        options.ai_solver=static_cast<Options::AIsolver>(config["ai_solver"].as<int>());
        options.server_or_client=static_cast<Options::SERVER_OR_CLIENT>(config["server_or_client"].as<int>());
    }else{
        std::cout<<"Usage: "<<argv[0]<<" [config_file]"<<std::endl;
        exit(1);
    }
    return options;
}


int main(int argc, char** argv){
    Options options=readFromArg(argc,argv);
    GridMap map(options.map_size,0.1);
    Food food(&map);
    Object object(&map);
    
    // std::cout<<"Welcome to Snake Game"<<std::endl;
    // std::cout<<"Choose Game Mode"<<std::endl;
    // std::cout<<"Single Player: 1"<<std::endl;
    // std::cout<<"Multi Player: 2"<<std::endl;
    // std::cout<<"AI: 3"<<std::endl;
    int map_size=options.map_size;
    int mode;
    switch (options.game_mode){
        case Options::MODE::single:
            mode=1;
            break;
        case Options::MODE::multi:
            mode=2;
            break;
        case Options::MODE::ai:
            mode=3;
            break;
    }
    int intervel;
    switch (options.game_speed){
        case Options::SPEED::low:
            intervel=200;
            break;
        case Options::SPEED::medium:
            intervel=100;
            break;
        case Options::SPEED::high:
            intervel=50;
            break;
    }
    int food_num=options.food_num;
    int object_num=options.object_num;
    // std::cin>>mode;

    if (mode==1){
        //单人模式
        Snake snake(&map,&food,5,5,Direction::UP,1);
        Human human(&snake);
        GameManager game(&map,&food,&object,{&human});
        VisualizeThread vis(&game, &snake, intervel);
        vis.start();
        game.start(food_num,object_num);
        game.run();
        vis.stop();
    }else if (mode==3){
        //AI模式
        if (options.ai_solver==Options::AIsolver::greedy){
            Snake snake(&map,&food,Direction::UP,1,{{5,5},{5,6}});
            PathSolver path_solver(&snake);
            GreedySolver greedy_solver(&snake,&path_solver);
            HamiltonSolver hamilton_solver(&snake,&path_solver);
            Ai ai(&snake,&greedy_solver);
            Human human(&snake);
            GameManager game(&map,&food,&object,{&ai});
            VisualizeThread vis(&game, &snake, intervel);
            vis.start();
        
            game.start(food_num,object_num);
        
            // while (1);
            game.run();
            vis.stop();
        }else{
            Snake snake(&map,&food,Direction::UP,1,{{5,5},{5,6}});
            PathSolver path_solver(&snake);
            GreedySolver greedy_solver(&snake,&path_solver);
            HamiltonSolver hamilton_solver(&snake,&path_solver);
            Ai ai(&snake,&hamilton_solver);
            Human human(&snake);
            GameManager game(&map,&food,&object,{&ai});
            VisualizeThread vis(&game,intervel);
            vis.start();
        
            game.start(food_num,object_num);
        
            // while (1);
            game.run();
            vis.stop();
        }
        
        
        
        
    }else{
        //双人模式
        //联网对战
        // Snake snake1(&map,&food,3,3,Direction::RIGHT,1);
        // Snake snake2(&map,&food,6,6,Direction::LEFT,1);
        // if (options.server_or_client==Options::SERVER_OR_CLIENT::server){
        //     NETWORK::Server server(&snake1, &snake2);
        //     server.StartServer();
        //     Human human1(&snake1,'w','s','a','d');
        //     GameManager game(&map,&food,&object,&human1);
        //     VisualizeThread vis(&game, &snake1, &snake2, intervel);
        //     std::thread networkThread([&server]() {
        //         server.Run();
        //     });
        //     vis.start();
        //     game.start(food_num,object_num);
        //     game.run();
        //     game.stop();
        //     vis.stop();
        //     networkThread.join();
        // }else if (options.server_or_client==Options::SERVER_OR_CLIENT::client){
        //     sf::TcpSocket socket;
        //     NETWORK::Client client(&snake1, &snake2, &socket);
        //     client.StartClient();
        //     Human human2(&snake2,'i','k','j','l');
        //     GameManager game(&map,&food,&object,&human2);
        //     VisualizeThread vis(&game, &snake1, &snake2, intervel);
        //     std::thread networkThread([&client]() {
        //         client.Run();
        //     });
        //     vis.start();
        //     game.start(food_num,object_num);
        //     game.run();
        //     game.stop();
        //     vis.stop();
        //     networkThread.join();
        // }else {
        //     std::cout<<"Error: server or client"<<std::endl;
        //     exit(1);
        // }
        
        //本地双人
        Snake snake1(&map,&food,3,3,Direction::RIGHT,1);
        Snake snake2(&map,&food,6,6,Direction::LEFT,1);
        Human human1(&snake1,'w','s','a','d');
        Human human2(&snake2,'i','k','j','l');
        GameManager game(&map,&food,&object,{&human1,&human2});
        VisualizeThread vis(&game, &snake1, &snake2, intervel);
        vis.start();
        game.start(food_num,object_num);
        game.run();
        game.stop();
        vis.stop();
        
    }

    
    
}

