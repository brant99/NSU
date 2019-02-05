//
// Created by anton on 16.12.18.
//

#include "Controller.h"
#include "Factory.h"
#include "BattleShipEx.h"
#include <memory>
#include <ConsoleView.h>
#include <iostream>
cxxopts::ParseResult Controller::parse(int argc, char **argv)  {
    cxxopts::Options options(argv[0]);
    options.add_options()("h,help","Help")
                         ("c,count","Rounds",cxxopts::value<int>()->default_value("1"))
                         ("f,first","FirstPlayer",cxxopts::value<std::string>())
                         ("s,second","SecondPlayer",cxxopts::value<std::string>());
    auto result=options.parse(argc,argv);
    if(result.count("h")) {
        std::cout<<options.help();
        exit(1);
    }
    return result;
}
bool Controller::verBuildShip( int type,std::string& begin,std::string& end) const {
    if ((type == 1 || type == 4) ? data->getAmount(type) * type < 4 : data->getAmount(type) * type < 6) {
        int strokeBeg = std::stoi(begin.substr(1, begin.length() - 1), nullptr, 10);
        int columnBeg = (begin[0] - 'a')+1;
        int strokeEnd = std::stoi(end.substr(1, end.length() - 1), nullptr, 10);
        int columnEnd = (end[0] - 'a')+1;
        std::string tmp;
        if (columnBeg <= 10 && columnBeg > 0 && columnEnd <= 10 && columnEnd > 0 &&
            strokeBeg <= 10 && strokeBeg > 0 && strokeEnd <= 10 && strokeEnd > 0) {
            if ((strokeEnd - strokeBeg == type - 1 && columnBeg == columnEnd) ||
                (columnEnd - columnBeg == type - 1 && strokeBeg == strokeEnd)) {
                strokeBeg = !(strokeBeg - 1) ? strokeBeg : strokeBeg - 1;
                strokeEnd = strokeEnd + 1 > 10 ? strokeEnd : strokeEnd + 1;
                columnBeg = !(columnBeg - 1) ? columnBeg : columnBeg - 1;
                columnEnd = columnEnd + 1 > 10 ? columnEnd : columnEnd + 1;
                for (int i = strokeBeg; i <= strokeEnd; i++)
                    for (int j = columnBeg; j <= columnEnd; j++) {
                        tmp = static_cast<char>('a' + (j - 1));
                        tmp += std::to_string(i);
                        if ('*' == data->getCell(data->getName(), tmp))
                            return false;
                    }
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}
void Controller::buildShip(std::vector<std::string> coordinates)  {
    std::string end,begin;
    begin=coordinates[1];
    if(coordinates.size()==3)
        end=coordinates[2];
    else
        end=begin;
    int type = std::stoi(coordinates[0], nullptr, 10);
    if(verBuildShip(type,begin,end)) {
        int begStroke=std::stoi(begin.substr(1,begin.length()-1), nullptr,10);
        int endStroke=std::stoi(end.substr(1,end.length()-1), nullptr,10);
        std::string currentPos=begin;
        if(begStroke==endStroke) {
            for (int i = 0; i < type; i++) {
                data->setCell( currentPos, '*');
                currentPos[0]++;
            }
        }
        else{
            for (int i = 0; i < type; i++) {
                currentPos = begin[0] + std::to_string(begStroke + i);
                data->setCell( currentPos, '*');
            }
        }
        data->setAmountShips(type,"add");
    }
    else
       throw BattleShipEx("invalid coordinates");
}

bool Controller::shoot(std::string pos) {
    data->swapPlayers();
    if(data->getCell(data->getName(),pos)=='*'){
        data->setCell(pos,'x');
        std::stack<std::string> killedShip=shipIsKilled(pos);
        if(!killedShip.empty()){
            data->setAmountShips(static_cast<int>(killedShip.size()),"sub");
            while(!killedShip.empty()){
                data->setCell(killedShip.top(),'F');
                killedShip.pop();
            }
        }
        data->swapPlayers();
        return true;
    }
    else if(data->getCell(data->getName(),pos)=='0'
        || data->getCell(data->getName(),pos)=='x'
        || data->getCell(data->getName(),pos)=='F') {
        data->swapPlayers();
        return false;
    }
    else {
        data->setCell(pos, '0');
        data->swapPlayers();
        return false;
    }
}
std::stack<std::string> Controller::shipIsKilled(std::string & cell) {
    std::stack<std::string> killedCells;
    int str;
   std::string tmp= cell;
   killedCells.push(cell);
    while(tmp[0]!=('a'-1)&& data->getCell(data->getName(),tmp)!='0'
            && data->getCell(data->getName(),tmp)!=' '){
        if(data->getCell(data->getName(),tmp)=='*') {
            while(!killedCells.empty())
                killedCells.pop();
            return killedCells;
        }
        if(tmp!=cell)
            killedCells.push(tmp);
        tmp[0]--;
    }
    tmp=cell;
    while(tmp[0]!=('j'+1) && data->getCell(data->getName(),tmp)!='0'
        && data->getCell(data->getName(),tmp)!=' '){
        if(data->getCell(data->getName(),tmp)=='*'){
            while(!killedCells.empty())
                killedCells.pop();
            return killedCells;
        }
        if(tmp!=cell)
            killedCells.push(tmp);
        tmp[0]++;
    }
    tmp=cell;
    str=std::stoi(tmp.substr(1,tmp.length()-1),0,10);
    while(str && data->getCell(data->getName(),tmp)!='0'
    && data->getCell(data->getName(),tmp)!=' '){
        if(data->getCell(data->getName(),tmp)=='*'){
            while(!killedCells.empty())
                killedCells.pop();
            return killedCells;
        }
        if(tmp!=cell)
            killedCells.push(tmp);
        str--;
        tmp=tmp[0]+ std::to_string(str);
    }
    tmp=cell;
    str=std::stoi(tmp.substr(1,tmp.length()-1),0,10);
    while(str<11 && data->getCell(data->getName(),tmp)!='0'
        && data->getCell(data->getName(),tmp)!=' '){
        if(data->getCell(data->getName(),tmp)=='*'){
            while(!killedCells.empty())
                killedCells.pop();
            return killedCells;
        }
        if(tmp!=cell)
            killedCells.push(tmp);
        str++;
        tmp=tmp[0]+ std::to_string(str);
    }
    return killedCells;
}

bool Controller::isOver() {
    data->swapPlayers();
    for(int i=1;i<=4;i++){
        if(data->getAmount(i)) {
            data->swapPlayers();
            return false;
        }
    }
    data->swapPlayers();
    return true;
}
bool Controller::readyToPlay() {
    for (int i = 1; i <5 ; ++i) {
        if((i == 1 || i == 4) ? data->getAmount(i) * i < 4 : data->getAmount(i) * i < 6)
            return false;
    }
    return true;
}

void Controller::play(int argc, char* argv[]) {
    Model data;
    ConsoleView view(&data);
    std::string player1="player1";
    std::string player2="player2";
    data.addPlayers(player1,player2);
    auto args=parse(argc,argv);
    int rounds=args["c"].as<int>();
    std::map<std::string,std::unique_ptr<Gamer>> players;
    players[player1].reset(FactoryGamer::Instance().Create(args["f"].as<std::string>()));
    players[player2].reset(FactoryGamer::Instance().Create(args["s"].as<std::string>()));
    while(rounds) {
        this->data = &data;
        view.draw();
        for (int i = 0; i < 2; ++i) {
            while (!readyToPlay()) {
                try {
                    buildShip(players[data.getName()]->buildShip());
                    view.draw();
                }
                catch (BattleShipEx &ex) {
                    std::cerr << ex.what() << std::endl;
                }
                //catch (std::exception &ex){
                //  return;
                //}
            }
            data.swapPlayers();
            view.draw();
        }
        while (!isOver()) {
            try {
                view.draw();
                while (shoot(players[data.getName()]->shoot()) && !isOver()) {
                    view.draw();
                }
                data.swapPlayers();
            }
            catch (BattleShipEx &ex) {
                std::cerr << ex.what() << std::endl;
            }

        }
        view.PrintWinner();
        data.clearFields();
        rounds--;
    }
}