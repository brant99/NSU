#ifndef CONEX_H
#define CONEX_H
#include <map>
#include <stack>
class ConExecute {
    std::stack <double > stack;
    std::map  <std::string,double > Var;
public:
    double getVal(const std::string &) const;
    void setVal(const std::string &,const double);
    void push(const double);
    double pop();
    double peek() const;
    int getSize() const;
};

#endif
