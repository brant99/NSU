//
// Created by anton on 11/30/18.
//

#include "Model.h"

int getPos(std::string &pos){
    int stroke=std::stoi(pos.substr(1,pos.length()-1), nullptr,10)-1;
    int column=pos[0]-'a';
    return stroke*10+column;
}

void Model::addPlayers (std::string& player1,std::string &player2) {
    std::vector<char> tmp(100,' ');
    fields[player1]=tmp;
    fields[player2]=tmp;
    this->user=player1;
    this->enemy=player2;
    std::vector<int> ships(4,0);
    amount[user]=ships;
    amount[enemy]=ships;
}
int Model::getAmount(int type) const {
    return amount.at(user)[type-1];
}

void Model::setCell(std::string & pos,const char value) {
    fields[user][getPos(pos)]=value;
}

char Model::getCell(const std::string &key, std::string & pos)const  {
    char value=const_cast<std::map <std::string,std::vector<char>> &>(fields)[key][getPos(pos)];
    return (key==user || value!='*') ? value : ' ';
}

std::string Model::getLine(const int number) const {
    std::string line="";
    std::string  players []= { user,enemy};
    std::string counter;
    for(int i=0;i<2;i++) {
        if(number<10)
            line+=" ";
        line+=std::to_string(number);
        counter="a";
        counter += std::to_string(number);
        for (; counter[0] < 'k'; counter[0]++)
            line += getCell(players[i], counter);
        line += "  ";
    }
    return line;
}
void Model::clearFields() {
    std::vector <char>tmp(100,' ');
    fields[user]=tmp;
    fields[enemy]=tmp;
}

std::string Model::getName()const {
    return user;
}


void Model::swapPlayers() {
    user.swap(enemy);
}
void Model::setAmountShips(int type,std::string com) {
    if(com=="add"){
        amount[user][type-1]++;
    }
    else if(com=="sub")
        amount[user][type-1]--;
}
