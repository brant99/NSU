#include "CommandFactory.h"
#include "../CalcEx.h"

CommandFactory& CommandFactory::Instance() {
    static CommandFactory factory;
    return factory;
}

void CommandFactory::RegisterMaker(const std::string &key, CreateCommand *maker) {
    if (_makers.find(key) != _makers.end())
    {
        throw CalcEx("Multiple makers for given key!");
    }
    _makers[key] = maker;
}

Command* CommandFactory::Create(const std::string &key) const {
    auto i = _makers.find(key);
    if (i == _makers.end())
    {
        throw CalcEx("Unrecognized object type!");
    }
    CreateCommand* maker = i->second;
    return maker->Create();
}
