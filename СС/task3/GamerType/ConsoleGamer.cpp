//
// Created by anton on 11/30/18.
//

#include <vector>
#include "ConsoleGamer.h"
#include "../Maker.h"
#include "../BattleShipEx.h"
static GamerMaker <ConsoleGamer> gamerMaker("console");
std::vector <std::string> parseLine(const std::string & strExec){
    std::vector <std::string>ls;
    size_t begin;
    for(begin=0;strExec[begin]==' ' && begin<strExec.length(); begin++){}
    for(size_t i=begin;i<strExec.length();++i){
        if(strExec[i]==' ') {
            ls.emplace_back(strExec.substr(begin , i-begin));
            for(;strExec[i]==' ' && i<strExec.length();i++){}
            begin=i;
        }
    }
    if(begin<strExec.length()) {
        ls.emplace_back(strExec.substr(begin, strExec.length()-begin));
    }
    return ls;
}

std::vector<std::string> ConsoleGamer::buildShip() const {
    std::string tmp;
    std::cout<<"print coordinates(begin,end)"<<std::endl;
    getline(std::cin,tmp);
    std::vector<std::string> coordinates = parseLine(tmp);
    size_t size = coordinates.size();
    if (size < 2 || size > 3)
        throw BattleShipEx("invalid amount of params");
    int type = std::stoi(coordinates[0], nullptr, 10);
    if ((size == 2 && type != 1)
    || type > 4 || type < 0)
        throw BattleShipEx("invalid type ship");
    if (type != 1 &&
        (static_cast<int>(coordinates[1][0] - coordinates[2][0]) > 0
        || std::stoi(coordinates[1].substr(1, coordinates[1].length() - 1), nullptr, 10)
        - std::stoi(coordinates[2].substr(1, coordinates[2].length() - 1), nullptr, 10) > 0))
        coordinates[1].swap(coordinates[2]);
    return coordinates;

}

std::string ConsoleGamer::shoot() const {
    std::string tmp;
    std::cout<<"print coordinate(shoot cell)"<<std::endl;
    std::getline(std::cin,tmp);
    std::vector<std::string> coordinates=parseLine(tmp);
    if(coordinates.size()!=1)
        throw BattleShipEx("invalid amount of params");
    if(static_cast<int>(coordinates[0][0]-'a')<0 ||
        static_cast<int>(coordinates[0][0]-'a')>9||
        std::stoi(coordinates[0].substr(1,coordinates[0].length()-1), nullptr,10)<1||
        std::stoi(coordinates[0].substr(1,coordinates[0].length()-1), nullptr,10)>10)
        throw BattleShipEx("invalid coordinates");
    return coordinates[0];
}
