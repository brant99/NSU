//
// Created by anton on 11/30/18.
//

#ifndef TASK3_OPTIMALGAMER_H
#define TASK3_OPTIMALGAMER_H


#include <vector>
#include "../Interfaces.h"
#include "../Model.h"

class OptimalGamer: public Gamer {
    std::vector<char> field;
    Model* model;
  //  int freeCellsAround(std::string);
    void setData(Model*);
    std::vector<std::string> buildShip() const override;
    std::string shoot() const override;
};


#endif //TASK3_OPTIMALGAMER_H
