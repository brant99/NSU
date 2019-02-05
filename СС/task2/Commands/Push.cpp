//
// Created by anton on 11/30/18.
//
#include "Push.h"
#include "CommandMaker.h"
#include "../CalcEx.h"

static CommandMaker <Push> maker("PUSH");

void Push::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size()!=1)
        throw CalcEx("Wrong amount args");
    isdigit(objects.top()[0]) ?
    context.push(std::stod(objects.top(),0)) :context.push(context.getVal(objects.top())) ;
}
