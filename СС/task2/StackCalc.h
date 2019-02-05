#ifndef STCCLK_H
#define STCCLK_H

#include <iostream>
#include <fstream>
#include "Commands/Command.h"
#include "ConExecute.h"

class StackCalc {
public:
    ConExecute context;
    void execute(std::istream &);
};

#endif