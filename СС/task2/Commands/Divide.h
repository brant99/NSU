//
// Created by anton on 11/26/18.
//

#ifndef TASK2_DIVIDE_H
#define TASK2_DIVIDE_H

#include "Command.h"

class Divide:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_DIVIDE_H
