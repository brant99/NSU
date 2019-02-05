//
// Created by anton on 11/30/18.
//

#ifndef TASK3_CONSOLEGAMER_H
#define TASK3_CONSOLEGAMER_H


#include "../Interfaces.h"
class ConsoleGamer:public Gamer{
    std::string shoot()const override;
    std::vector<std::string> buildShip() const override;
};

#endif //TASK3_CONSOLEGAMER_H
