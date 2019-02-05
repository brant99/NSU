#ifndef CMNDMK_H
#define CMNDMK_H

#include "Command.h"
#include "CommandFactory.h"


template<typename T>
class CommandMaker : public CreateCommand
{
public:
    CommandMaker(const std::string & key){
        CommandFactory::Instance().RegisterMaker(key,this);
    }
    virtual Command * Create() const override
    {
        return new T();
    }
    virtual ~CommandMaker()override {
    };
};

#endif