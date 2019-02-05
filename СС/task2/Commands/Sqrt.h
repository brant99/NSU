//
// Created by anton on 11/26/18.
//

#ifndef TASK2_SQRT_H
#define TASK2_SQRT_H

#include "Command.h"

class Sqrt:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_SQRT_H
