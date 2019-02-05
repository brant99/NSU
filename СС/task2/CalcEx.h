//
// Created by anton on 16.12.18.
//

#ifndef TASK2_MYEXCEPTION_H
#define TASK2_MYEXCEPTION_H

#include <exception>
#include <string>
class CalcEx:public std::exception{
    const char* message;
public:
    CalcEx(const char* message){
        this->message=message;
    }
    const char* what() const throw() override{
        return message;
    }
};
#endif //TASK2_MYEXCEPTION_H
