//
// Created by anton on 24.12.18.
//

#ifndef TASK4_CSVPARSER_H
#define TASK4_CSVPARSER_H


#include <tuple>
#include <fstream>
#include <vector>
#include "tuple.h"

template<class ...Types>class CSVParser {
    template <class arg>
    arg parseLine(std::string&);
    std::vector<std::tuple<Types...>> data;
public:
    typedef tuple<Types...> it;
    CSVParser(std::ifstream &, int);
    it begin();
    it end();
};

#endif //TASK4_CSVPARSER_H
