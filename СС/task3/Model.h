//
// Created by anton on 11/30/18.
//

#ifndef TASK3_MODEL_H
#define TASK3_MODEL_H

#include<vector>
#include <map>
#include "Interfaces.h"

class Model {
    std::map <std::string,std::vector<char>>fields;
    std::string user;
    std::string enemy;
    std::map<std::string,std::vector <int>>amount;
public:
    void addPlayers(std::string& player1,std::string &player2);
    char getCell(const std::string &,std::string &) const;
    void setCell(std::string &,const char);
    int getAmount(int) const;
    std::string getName() const;
    std::string getLine(const int) const;
    void swapPlayers() ;
    void clearFields();
    void setAmountShips(int type,std::string);
};


#endif //TASK3_MODEL_H
