//
// Created by anton on 11/30/18.
//

#include <iostream>
#include "Print.h"
#include "CommandMaker.h"
#include "../CalcEx.h"

static CommandMaker <Print> maker("PRINT");

void Print::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size())
        throw CalcEx("Wrong amount args");
    if(!context.getSize())
        throw CalcEx("stack is empty");
    std::cout<<context.peek()<<std::endl;
}