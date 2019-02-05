#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>
int main(int argc, char** argv)
{
	std::cout <<  "Hello world!" << "\n";

  //  std::cout << Module1::getMyName() << "\n";
    //std::cout << Module2::getMyName() << "\n";

    //std::cout << Module1::getMyName() << "\n"; // (A) John
    //std::cout << Module2::getMyName() << "\n";

    //std::cout << Module2::getMyName() << "\n"; // COMPILATION ERROR (C)
    //std::cout << Module2::getMyName() << "\n"; // (D) James
    //std::cout << Module3::getMyName() << "\n";
}
//чтобы использовать cout вместо std::cout можно использовать пространство имен std (using namespace std)
//в B и D возникает ошибка тк используется второе пространство имен,чего быть не может
