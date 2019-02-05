//
// Created by anton on 11/30/18.
//
#ifndef TASK3_INTERFACES_H
#define TASK3_INTERFACES_H

#include <iostream>
#include <vector>
class GameView{
public:
    virtual void PrintWinner()=0;
    virtual void draw()=0;
    virtual ~GameView()= default;
};

class Gamer{
public:
    virtual std::vector <std::string> buildShip() const=0;
    virtual std::string shoot() const=0;
    virtual ~Gamer()= default;
};

class GamerCreate{
public:
    virtual Gamer * Create()const =0;
    virtual ~GamerCreate()= default;
};

#endif //TASK3_INTERFACES_H
