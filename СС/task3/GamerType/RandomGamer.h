//
// Created by anton on 11/30/18.
//

#ifndef TASK3_RANDOMGAMER_H
#define TASK3_RANDOMGAMER_H


#include "../Interfaces.h"

class RandomGamer: public Gamer {
    std::vector<std::string> buildShip() const override;
    std::string shoot() const override;
};


#endif //TASK3_RANDOMGAMER_H
