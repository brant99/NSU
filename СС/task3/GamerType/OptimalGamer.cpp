//
// Created by anton on 11/30/18.
//

#include "OptimalGamer.h"
#include "../Maker.h"
#include <random>
static GamerMaker <OptimalGamer> gamerMaker("optimal");
//int OptimalGamer::freeCellsAround(std::string & pos ) {

//}
std::vector<std::string> OptimalGamer::buildShip() const {
    std::vector<std::string> data;
    std::random_device rd;
    int type= static_cast<int>(rd()%4+1);
    while((type == 1 || type == 4) ? model->getAmount(type) * type >= 4 : model->getAmount(type) * type >= 6)
        type=rd()%4+1;
    if(!model->getAmount(type)){

    }
}

std::string OptimalGamer::shoot() const {

}
void OptimalGamer::setData(Model *) {
    this->model=model;
    std::vector<char> tmp(100,' ');
    field=tmp;
}