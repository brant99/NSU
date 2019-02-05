//
// Created by anton on 11/30/18.
//

#include "RandomGamer.h"
#include "../Maker.h"
#include <random>
static GamerMaker <RandomGamer> gamerMaker("random");
std::string RandomGamer::shoot() const {
    std::string shot;
    std::random_device rd;
    shot= static_cast<char>('a'+(rd()%10));
    shot+= std::to_string(rd()%10+1);
    return shot;
}

std::vector<std::string> RandomGamer::buildShip() const {
    std::vector<std::string> data;
    std::random_device rd;
    std::string tmp;
    tmp= static_cast<char>('a'+(rd()%10));
    data.emplace_back(std::to_string(rd()%4 +1));
    data.emplace_back( tmp);
    data[1]+= std::to_string(rd()%10+1);
    if(std::stoi(data[0],0,10)!=1) {
        if (rd() % 2) {
            if (data[1][0] + std::stoi(data[0], nullptr, 10) <= 'a' + 10) {
                tmp = static_cast<char>(data[1][0] + std::stoi(data[0], nullptr, 10) - 1);
                data.emplace_back(tmp);
                data[2] += data[1].substr(1, data[1].length() - 1);
            }
            else {
                tmp = static_cast<char>(data[1][0] - std::stoi(data[0], nullptr, 10) + 1);
                data.emplace_back(tmp);
                data[2] += data[1].substr(1, data[1].length() - 1);
                data[1].swap(data[2]);
            }
        }
        else {
            tmp = data[1][0];
            data.emplace_back(tmp);
            if (std::stoi(data[1].substr(1, data[1].length() - 1), nullptr, 10) + std::stoi(data[0], nullptr, 10) <=
                11) {
                data[2] += std::to_string(std::stoi(data[1].substr(1, data[1].length() - 1), nullptr, 10) +
                        std::stoi(data[0], nullptr, 10) - 1);
            } else {
                data[2] += std::to_string(std::stoi(data[1].substr(1, data[1].length() - 1), nullptr, 10) -
                        std::stoi(data[0], nullptr, 10) + 1);
                data[2].swap(data[1]);
            }
        }
    }
    return data;
}