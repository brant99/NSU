#ifndef COMMAND_H
#define COMMAND_H

#include <../ConExecute.h>
#include <string>
class Command{
public:
    virtual void execute(ConExecute &,std::stack <std::string> &) const=0;
    virtual ~Command()= default;
};
class CreateCommand{
public:
    virtual Command* Create() const=0;
    virtual ~CreateCommand()= default;
};

#endif