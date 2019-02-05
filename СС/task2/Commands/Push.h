//
// Created by anton on 11/30/18.
//

#ifndef TASK2_PUSH_H
#define TASK2_PUSH_H
#include "Command.h"

class Push:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_PUSH_H
