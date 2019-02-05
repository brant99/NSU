//
// Created by anton on 24.12.18.
//

#include "CSVParser.h"
#include "tuple.h"
template <class T>
struct Converter {
    static std::string Fromstring(std::string const &str){
        return str;
    }
};
template <>
struct Converter <int>{
    static int Fromstring(std::string const &str){
        return std::stoi(str, 0, 10);
    }
};
template <>
struct Converter <float>{
    static float Fromstring(std::string const &str){
        return std::stof(str, 0);
    }
};

template <>
struct Converter <char>{
    static float Fromstring(std::string const &str){
        return str[0];
    }
};

template <>
struct Converter <double>{
    static double Fromstring(std::string const &str){
        return std::stod(str, 0);
    }
};

template <class...Types>
template <class arg>
arg CSVParser<Types...>::parseLine(std::string & line) {
    for(size_t i=line.length()-1;i>=0 ;i--){
        if(line[i]==','){
            std::string tmp=line.substr(i+1,(line.length()-1)-i);
            line=line.substr(0,i);
            return Converter<arg>::Fromstring(tmp);
        }
        if(i==0){
            std::string tmp=line.substr(i,(line.length())-i);
            return Converter<arg>::Fromstring(tmp);
        }
    }
}

template <class ... Types>
CSVParser<Types...>::CSVParser(std::ifstream &file , int count) {
    std::string skip;
    for(;count>0;count--)
        std::getline(file,skip);
    while(std::getline(file,skip)) {
        data.push_back(std::tuple_cat(std::make_tuple(parseLine<Types>(skip))...));
    }
};


template <class ... Types>
typename CSVParser<Types...>::it CSVParser<Types...>::begin() {
    return tuple<Types...>(data.front());
}

template <class ... Types>
typename CSVParser<Types...>::it CSVParser<Types...>::end() {
    return tuple<Types...>(data.back());
}