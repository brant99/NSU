//
// Created by anton on 17.12.18.
//

#ifndef TASK3_FACTORY_H
#define TASK3_FACTORY_H


#include <map>
#include "Interfaces.h"

class FactoryGamer {
public:
    static FactoryGamer& Instance();
    Gamer * Create(std::string)const;
    void RegisterMakerGame(std::string,GamerCreate *);
private:
    std::map<std::string, GamerCreate*> makersGamer;
};


#endif //TASK3_FACTORY_H
