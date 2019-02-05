//
// Created by anton on 17.12.18.
//

#ifndef TASK3_MAKER_H
#define TASK3_MAKER_H

#include "Interfaces.h"
#include "Factory.h"

template<typename T>
class GamerMaker : public GamerCreate
{
public:
    GamerMaker(std::string key){
        FactoryGamer::Instance().RegisterMakerGame(key,this);
    }
    Gamer * Create() const override
    {
        return new T();
    }
};
#endif //TASK3_MAKER_H
