#ifndef COMMANDFac_H
#define COMMANDFac_H

#include "Command.h"
class CommandFactory {
    std::map<std::string,CreateCommand*> _makers;
public:
    static CommandFactory& Instance();
    void RegisterMaker(const std::string& key,CreateCommand  * maker);
    Command *Create(const std::string &) const;
};

#endif