//
// Created by anton on 11/30/18.
//

#ifndef TASK2_MULTIPLY_H
#define TASK2_MULTIPLY_H

#include "Command.h"

class Multiply: public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_MULTIPLY_H
