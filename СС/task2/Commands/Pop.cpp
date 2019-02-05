//
// Created by anton on 11/30/18.
//

#include "Pop.h"
#include "CommandMaker.h"
#include "../CalcEx.h"

static CommandMaker <Pop> maker("POP");

void Pop::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size())
        throw CalcEx("Wrong amount args");
    if(!context.getSize())
        throw CalcEx("stack is empty");
    context.pop();
}