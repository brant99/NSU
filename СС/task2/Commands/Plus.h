//
// Created by anton on 11/30/18.
//

#ifndef TASK2_PLUS_H
#define TASK2_PLUS_H

#include "Command.h"

class Plus:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_PLUS_H
