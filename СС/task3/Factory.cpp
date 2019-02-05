//
// Created by anton on 17.12.18.
//

#include "Factory.h"
FactoryGamer& FactoryGamer::Instance() {
    static FactoryGamer factoryGame;
    return factoryGame;
}
void FactoryGamer::RegisterMakerGame(std::string key, GamerCreate * maker) {
    if (makersGamer.find(key) != makersGamer.end())
    {
       // throw new std::exception("Multiple makers for given key!");
    }
    makersGamer[key] = maker;
}
Gamer* FactoryGamer::Create(std::string key) const {
    auto i = makersGamer.find(key);
    if (i == makersGamer.end()) {
        //throw new std::exception("Unrecognized object type!");
    }
    return i->second->Create();
}