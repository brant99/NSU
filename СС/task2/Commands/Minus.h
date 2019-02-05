//
// Created by anton on 11/30/18.
//

#ifndef TASK2_MINUS_H
#define TASK2_MINUS_H

#include "Command.h"

class Minus:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_MINUS_H
