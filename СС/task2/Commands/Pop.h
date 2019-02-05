//
// Created by anton on 11/30/18.
//

#ifndef TASK2_POP_H
#define TASK2_POP_H

#include "Command.h"

class Pop: public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_POP_H
