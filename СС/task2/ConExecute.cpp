#include "ConExecute.h"
#include <iostream>
#include "CalcEx.h"
double  ConExecute::getVal(const std::string & key) const{
    if(Var.find(key)==Var.end())
        throw CalcEx("Wrong key");
    return const_cast<std::map <std::string,double> &>(Var)[key];
}
void ConExecute::setVal(const std::string & key,const double num) {
    if(Var.find(key)!=Var.end())
        throw CalcEx("variable is using");
    Var[key]=num;
}
void ConExecute::push(const double num) {
    stack.push(num);
}
double ConExecute::pop() {
    double num;
    num = stack.top();
    stack.pop();
    return num;
}
double ConExecute::peek() const{
    return stack.top();
}
int ConExecute::getSize() const{
    return stack.size();
}
