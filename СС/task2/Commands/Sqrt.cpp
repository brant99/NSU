//
// Created by anton on 11/26/18.
//

#include "Sqrt.h"
#include "CommandMaker.h"
#include "../CalcEx.h"
#include <cmath>
static CommandMaker <Sqrt> maker("SQRT");

void Sqrt::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size())
        throw CalcEx("Wrong amount args");
    if(context.getSize()<1)
        throw CalcEx("stack don't have so many numbers");
    double  Num=context.pop();
    if(Num<0)
        throw CalcEx("sqrt from negative number");
    context.push(sqrt(Num));
}