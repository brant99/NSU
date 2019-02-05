#include "StackCalc.h"
#include "Define.h"
int main(int argc,char * argv[]) {
    StackCalc calc;
    if(argc==1)
        calc.execute(std::cin);
    else {
        std::ifstream file=std::ifstream(argv[1]);
        calc.execute(file);
    }
    return 0;
}