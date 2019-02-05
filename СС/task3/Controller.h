//
// Created by anton on 16.12.18.
//

#ifndef TASK3_CONTROLLER_H
#define TASK3_CONTROLLER_H


#include "Interfaces.h"
#include <stack>
#include "Model.h"
#include <cxxopts.hpp>

#define playerInfo struct PlayerInfo

playerInfo{
    std::string name;
    std::string type;
};

class Controller {
    Model * data;
    bool verBuildShip( int,std::string &,std::string &)const;
    void buildShip(std::vector<std::string> ) ;
    bool shoot(std::string ) ;
    bool isOver();
    bool readyToPlay();
    cxxopts::ParseResult parse(int argc, char* argv[]);
    std::stack<std::string> shipIsKilled(std::string &);
public:
    void play(int argc, char* argv[]);
};


#endif //TASK3_CONTROLLER_H
