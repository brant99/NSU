//
// Created by anton on 19.12.18.
//

#ifndef TASK3_BATTLESHIPEX_H
#define TASK3_BATTLESHIPEX_H

#include <bits/exception.h>
#include <string>
class BattleShipEx: public std::exception{
public:
    char const *message;
    BattleShipEx(char const * ex){
        message=ex;
    }
    const char* what() const throw() override{
        return message;
    }
};
#endif //TASK3_BATTLESHIPEX_H
