#include "StackCalc.h"
#include "CommandFactory.h"
#include <exception>
#include <memory>
#include "CalcEx.h"
std::stack <std::string> parseLine(const std::string & strExec){
    std::stack <std::string>ls;
    int begin;
    for(begin=0;strExec[begin]==' ' && begin<strExec.length(); begin++){}
    for(int i=begin;i<strExec.length();i++){
        if(strExec[i]==' ') {
            ls.push(strExec.substr(begin , i-1));
            for(;strExec[i]==' ' && i<strExec.length();i++){}
            begin=i;
        }
    }
    if(begin<strExec.length()) {
        ls.push(strExec.substr(begin, strExec.length() - 1));
    }
    return ls;
}

std::string getName(std::string & strExec) {
    int begin,end;
    std::string nameCom;
    //try {
        for (begin = 0; strExec[begin] == ' ' && begin < strExec.length(); begin++) {}
        if(begin==strExec.length())
            throw CalcEx("string is empty");
        for (end = begin; end < strExec.length() && strExec[end] != ' '; end++) {}
        nameCom = strExec.substr(begin, end );
        strExec = strExec.substr(end, strExec.length() - 1);
        return nameCom;
    //}
    //catch (CalcEx & ex){
    //    throw ex.what();
    //}
}

void StackCalc::execute(std::istream &file) {
    std::string strExec;
    while(getline(file,strExec)) {
        try {
            std::string nameCommand;
            std::stack<std::string> objects;
            nameCommand = getName(strExec);
            objects = parseLine(strExec);
            std::unique_ptr<Command> currentCommand(CommandFactory::Instance().Create(nameCommand));
            currentCommand->execute(context,objects);
        }
        catch (std::exception &ex){
            std::cerr<<ex.what()<<std::endl;
        }
    }
}