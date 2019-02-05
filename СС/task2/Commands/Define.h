#ifndef DEF_H
#define DEF_H

#include "Command.h"
#include "CommandMaker.h"
class Define:public Command {
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const override;
};

#endif