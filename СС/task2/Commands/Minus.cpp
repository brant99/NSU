//
// Created by anton on 11/30/18.
//

#include "Minus.h"
#include "CommandMaker.h"
#include "../CalcEx.h"

static CommandMaker <Minus> maker("-");

void Minus::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size())
        throw CalcEx("Wrong amount args");
    if(context.getSize()<2)
        throw CalcEx("stack don't have so many numbers");
    double firNum=context.pop();
    double secNum=context.pop();
    context.push(secNum-firNum);
}