//
// Created by anton on 11/30/18.
//

#ifndef TASK2_PRINT_H
#define TASK2_PRINT_H

#include "Command.h"

class Print: public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};


#endif //TASK2_PRINT_H
