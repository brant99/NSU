//
// Created by anton on 11/26/18.
//

#include "Divide.h"
#include "CommandMaker.h"
#include "../CalcEx.h"

static CommandMaker <Divide> maker("/");

void Divide::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size())
        throw CalcEx("Wrong amount args");
    if(context.getSize()<2)
        throw CalcEx("stack don't have so many numbers");
    double firNum=context.pop();
    if(firNum==0)
        throw CalcEx("divide by 0");
    double secNum=context.pop();
    context.push(secNum/firNum);
}