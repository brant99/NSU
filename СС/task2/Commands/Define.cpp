#include <iostream>
#include "Define.h"
#include "../CalcEx.h"

static CommandMaker <Define> maker("DEFINE");

void Define::execute(ConExecute & context, std::stack<std::string> & objects) const {
    if(objects.size()!=2)
        throw CalcEx("Wrong amount args");
    double value= std::stod(objects.top(),0);
    objects.pop();
    context.setVal(objects.top(), value);
    objects.pop();
}




